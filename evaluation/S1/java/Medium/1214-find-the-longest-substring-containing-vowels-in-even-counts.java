// Source: https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/   |   Difficulty: Medium
//
// Problem Description:
// Given the string s, return the size of the longest substring containing each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.
//
// Example:
// Input: s = "eleetminicoworoep"
// Output: 13
// Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.
//
// Constraints:
// 1 <= s.length <= 5 x 10^5
// 	s contains only lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
//   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
//   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
//   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
//   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
//   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
//   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
//   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
//   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
//   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int findTheLongestSubstring(String s) {
        int n = s.length();
        int[] pos = new int[32];
        for (int i = 0; i < 32; i++) {
            pos[i] = -1;
        }
        pos[0] = 0;

        int state = 0;
        int maxLen = 0;

        for (int i = 0; i < n; i++) {
            char ch = s.charAt(i);
            if (ch == 'a') {
                state ^= 1 << 0;
            } else if (ch == 'e') {
                state ^= 1 << 1;
            } else if (ch == 'i') {
                state ^= 1 << 2;
            } else if (ch == 'o') {
                state ^= 1 << 3;
            } else if (ch == 'u') {
                state ^= 1 << 4;
            }

            if (pos[state] >= 0) {
                maxLen = Math.max(maxLen, i + 1 - pos[state]);
            } else {
                pos[state] = i + 1;
            }
        }

        return maxLen;          
    }
}
