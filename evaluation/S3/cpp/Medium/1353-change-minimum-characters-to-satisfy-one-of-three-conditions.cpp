// Source: https://leetcode.com/problems/change-minimum-characters-to-satisfy-one-of-three-conditions/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings a and b that consist of lowercase letters. In one operation, you can change any character in a or b to any lowercase letter.
//
// Your goal is to satisfy one of the following three conditions:
//
//
// 	Every letter in a is strictly less than every letter in b in the alphabet.
// 	Every letter in b is strictly less than every letter in a in the alphabet.
// 	Both a and b consist of only one distinct letter.
//
//
// Return the minimum number of operations needed to achieve your goal.
//
// Example:
// Input: a = "aba", b = "caa"
// Output: 2
// Explanation: Consider the best way to make each condition true:
// 1) Change b to "ccc" in 2 operations, then every letter in a is less than every letter in b.
// 2) Change a to "bbb" and b to "aaa" in 3 operations, then every letter in b is less than every letter in a.
// 3) Change a to "aaa" and b to "aaa" in 2 operations, then a and b consist of one distinct letter.
// The best way was done in 2 operations (either condition 1 or condition 3).
//
// Constraints:
// 1 <= a.length, b.length <= 105
// 	a and b consist only of lowercase letters.
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - Z-function and its calculation (string, array, counting)
//   • When to use: Use when you need to find all occurrences of a pattern within a text, or to identify repeated prefixes within a string efficiently.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the string and its suffix starting at index i. It runs in linear time, O(N), where N is the length of the string.
//   • Invariants: For all j < i, z[j] correctly stores the length of the longest common prefix between S and S[j...].; The segment [l, r-1] represents the rightmost segment that is a prefix of S and has been fully processed.
//   • Tips: Initialize z[0] to 0 (or N, depending on definition) and handle it as a base case.; Utilize previously computed Z-values to avoid redundant comparisons, especially within the 'rightmost matching segment' [l, r].
//   • Pitfalls: Incorrectly updating or using the 'rightmost matching segment' boundaries (l and r).; Off-by-one errors when calculating indices or lengths, especially with 0-based vs. 1-based indexing.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minCharacters(string a, string b) {
        vector<int> countA(26, 0), countB(26, 0);
        for (char c : a) ++countA[c - 'a'];
        for (char c : b) ++countB[c - 'a'];

        int minOps = INT_MAX;
        // Condition 1: Every letter in a is strictly less than every letter in b
        for (int i = 1; i < 26; ++i) {
            int ops = accumulate(countA.begin() + i, countA.end(), 0) + accumulate(countB.begin(), countB.begin() + i, 0);
            minOps = min(minOps, ops);
        }

        // Condition 2: Every letter in b is strictly less than every letter in a
        for (int i = 1; i < 26; ++i) {
            int ops = accumulate(countB.begin() + i, countB.end(), 0) + accumulate(countA.begin(), countA.begin() + i, 0);
            minOps = min(minOps, ops);
        }

        // Condition 3: Both a and b consist of only one distinct letter
        for (int i = 0; i < 26; ++i) {
            int ops = (a.size() - countA[i]) + (b.size() - countB[i]);
            minOps = min(minOps, ops);
        }

        return minOps;          
    }
};
