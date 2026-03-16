// Source: https://leetcode.com/problems/regular-expression-matching/   |   Difficulty: Hard
//
// Problem Description:
// Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:
//
//
// 	'.' Matches any single character.​​​​
// 	'*' Matches zero or more of the preceding element.
//
//
// The matching should cover the entire input string (not partial).
//
// Example:
// Input: s = "aa", p = "a"
// Output: false
// Explanation: "a" does not match the entire string "aa".
//
// Constraints:
// 1 <= s.length <= 20
// 	1 <= p.length <= 20
// 	s contains only lowercase English letters.
// 	p contains only lowercase English letters, '.', and '*'.
// 	It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.
//
// Helpful references (internal KB):
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
//   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
//   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
//   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
//   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
// - Substring Search (string, array, kmp)
//   • When to use: Use when needing to find all occurrences or the first occurrence of a pattern string within a larger text string efficiently. It is particularly useful when the pattern might have significant self-overlapping prefixes and suffixes, allowing for linear time complexity.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently searches for occurrences of a pattern within a text by avoiding redundant comparisons. It preprocesses the pattern to build a Deterministic Finite Automaton (DFA) or Longest Proper Prefix Suffix (LPS) array, achieving O(N + M) time complexity.
//   • Invariants: During DFA construction, dfa[c][j] correctly stores the next state if character c is encountered in state j.; During DFA construction, x maintains the length of the longest proper prefix of pattern[0...j-1] that is also a suffix of pattern[0...j-1].
//   • Tips: Precompute the LPS array or DFA for the pattern to guide the search.; The LPS array indicates the longest proper prefix that is also a suffix, enabling efficient shifts.
//   • Pitfalls: Incorrect construction of the LPS array or DFA is a common source of errors.; High constant factors for small alphabets or short patterns might make simpler algorithms faster.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool isMatch(string s, string p) {
         int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;

        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*' && j > 1) {
                dp[0][j] = dp[0][j - 2];
            }
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2] || ((p[j - 2] == s[i - 1] || p[j - 2] == '.') && dp[i - 1][j]);
                } else {
                    dp[i][j] = (p[j - 1] == s[i - 1] || p[j - 1] == '.') && dp[i - 1][j - 1];
                }
            }
        }

        return dp[m][n];        
        
    }
};
