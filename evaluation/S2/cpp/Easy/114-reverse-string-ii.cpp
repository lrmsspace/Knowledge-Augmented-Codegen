// Source: https://leetcode.com/problems/reverse-string-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s and an integer k, reverse the first k characters for every 2k characters counting from the start of the string.
//
// If there are fewer than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, then reverse the first k characters and leave the other as original.
//
// Example:
// Input: s = "abcdefg", k = 2
// Output: "bacdfeg"
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of only lowercase English letters.
// 	1 <= k <= 104
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Binary Exponentiation (number, mod-exp, divide-and-conquer)
//   • When to use: Use when calculating a^n efficiently, especially for large n or when results need to be taken modulo some number. It reduces the number of multiplications from linear to logarithmic.
//   • Idea: Binary exponentiation computes a^n by repeatedly squaring the base and multiplying terms corresponding to the set bits in the exponent's binary representation. This method achieves a time complexity of O(log n) multiplications.
//   • Invariants: The product of `result` and `current_base` raised to the `remaining_exponent` equals the initial `a^N`.; `current_base` always represents `a` raised to the power of `2^k` for the current iteration `k`.
//   • Tips: Handle base cases like n=0 (result is 1) and n=1 (result is a).; Use long long or appropriate large integer types for intermediate products to prevent overflow.
//   • Pitfalls: Integer overflow if not using appropriate data types or modulo arithmetic.; Incorrectly handling negative exponents (typically not covered by basic binary exponentiation).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += 2 * k) {
            int left = i, right = min(i + k - 1, (int)s.size() - 1);
            while (left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }
        return s;           
    }
};
