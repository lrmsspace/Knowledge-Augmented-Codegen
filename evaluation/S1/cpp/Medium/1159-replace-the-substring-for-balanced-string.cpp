// Source: https://leetcode.com/problems/replace-the-substring-for-balanced-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s of length n containing only four kinds of characters: 'Q', 'W', 'E', and 'R'.
//
// A string is said to be balanced if each of its characters appears n / 4 times where n is the length of the string.
//
// Return the minimum length of the substring that can be replaced with any other string of the same length to make s balanced. If s is already balanced, return 0.
//
// Example:
// Input: s = "QWER"
// Output: 0
// Explanation: s is already balanced.
//
// Constraints:
// n == s.length
// 	4 <= n <= 105
// 	n is a multiple of 4.
// 	s contains only 'Q', 'W', 'E', and 'R'.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - String Hashing (string, array, hashing)
//   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
//   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
//   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
//   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
//   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int balancedString(string s) {
        int n = s.size();
        int target = n / 4;
        int count[4] = {0}; // Q, W, E, R

        for (char c : s) {
            switch (c) {
                case 'Q': count[0]++; break;
                case 'W': count[1]++; break;
                case 'E': count[2]++; break;
                case 'R': count[3]++; break;
            }
        }

        if (count[0] == target && count[1] == target && count[2] == target && count[3] == target) {
            return 0; // already balanced
        }

        int left = 0, right = 0;
        int minLength = n;

        while (right < n) {
            switch (s[right]) {
                case 'Q': count[0]--; break;
                case 'W': count[1]--; break;
                case 'E': count[2]--; break;
                case 'R': count[3]--; break;
            }
            right++;

            while (left < n && count[0] <= target && count[1] <= target && count[2] <= target && count[3] <= target) {
                minLength = min(minLength, right - left);
                switch (s[left]) {
                    case 'Q': count[0]++; break;
                    case 'W': count[1]++; break;
                    case 'E': count[2]++; break;
                    case 'R': count[3]++; break;
                }
                left++;
            }
        }

        return minLength;           
    }
};
