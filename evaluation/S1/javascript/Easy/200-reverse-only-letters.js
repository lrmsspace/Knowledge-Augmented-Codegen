// Source: https://leetcode.com/problems/reverse-only-letters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, reverse the string according to the following rules:
//
//
// 	All the characters that are not English letters remain in the same position.
// 	All the English letters (lowercase or uppercase) should be reversed.
//
//
// Return s after reversing it.
//
// Example:
// Input: s = "ab-cd"
// Output: "dc-ba"
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of characters with ASCII values in the range [33, 122].
// 	s does not contain '\"' or '\\'.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - String Sorts (array, string, number, radix-sort, counting-sort)
//   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
//   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
//   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
//   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
//   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
// - Minkowski sum of convex polygons (geometry, array, two-pointers)
//   • When to use: When needing to compute the sum of two convex polygons, or efficiently determine the minimum distance or intersection between them.
//   • Idea: The Minkowski sum of two convex polygons P and Q is a new convex polygon formed by vector addition of all points from P and Q. It can be computed in O(|P| + |Q|) time by merging their edge vectors.
//   • Invariants: The current edge added to the Minkowski sum is the one with the smallest angle among the remaining edges from both polygons.; The sequence of edges in the Minkowski sum maintains convexity.
//   • Tips: The vertices of P+Q are sums of vertices of P and Q.; The edges of P+Q are the edges of P and Q, sorted by angle.
//   • Pitfalls: Incorrectly handling edge cases like collinear edges or degenerate polygons.; Floating point precision issues in geometric calculations.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {string}
 */
var reverseOnlyLetters = function(s) {
    const isLetter = (c) => {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    };

    let arr = s.split('');
    let left = 0;
    let right = arr.length - 1;
    while (left < right) {
        if (!isLetter(arr[left])) {
            left++;
        } else if (!isLetter(arr[right])) {
            right--;
        } else {
            [arr[left], arr[right]] = [arr[right], arr[left]];
            left++;
            right--;
        }
    }
    return arr.join('');
};
