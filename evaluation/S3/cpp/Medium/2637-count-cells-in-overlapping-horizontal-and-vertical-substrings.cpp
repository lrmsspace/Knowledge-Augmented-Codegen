// Source: https://leetcode.com/problems/count-cells-in-overlapping-horizontal-and-vertical-substrings/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix grid consisting of characters and a string pattern.
//
// A horizontal substring is a contiguous sequence of characters read from left to right. If the end of a row is reached before the substring is complete, it wraps to the first column of the next row and continues as needed. You do not wrap from the bottom row back to the top.
//
// A vertical substring is a contiguous sequence of characters read from top to bottom. If the bottom of a column is reached before the substring is complete, it wraps to the first row of the next column and continues as needed. You do not wrap from the last column back to the first.
//
// Count the number of cells in the matrix that satisfy the following condition:
//
//
// 	The cell must be part of at least one horizontal substring and at least one vertical substring, where both substrings are equal to the given pattern.
//
//
// Return the count of these cells.
//
// Example:
// Input: grid = [["a","a","c","c"],["b","b","b","c"],["a","a","b","a"],["c","a","a","c"],["a","a","b","a"]], pattern = "abaca"
//
// Output: 1
//
// Explanation:
//
// The pattern "abaca" appears once as a horizontal substring (colored blue) and once as a vertical substring (colored red), intersecting at one cell (colored purple).
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	1 <= pattern.length <= m * n
// 	grid and pattern consist of only lowercase English letters.
//
// Helpful references (internal KB):
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
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
    int countCells(vector<vector<char>>& grid, string pattern) {
        int m = grid.size(), n = grid[0].size(), p = pattern.size();
        vector<int> h(m * n), v(m * n);
        for (int i = 0; i < m * n; ++i) {
            h[i] = (grid[i / n][i % n] == pattern[i % p]) ? (i > 0 ? h[i - 1] : 0) + 1 : 0;
            v[i] = (grid[i / n][i % n] == pattern[i % p]) ? (i >= n ? v[i - n] : 0) + 1 : 0;
        }
        int ans = 0;
        for (int i = 0; i < m * n; ++i) {
            if (h[i] >= p && v[i] >= p) {
                ++ans;
            }
        }
        return ans;         
    }
};
