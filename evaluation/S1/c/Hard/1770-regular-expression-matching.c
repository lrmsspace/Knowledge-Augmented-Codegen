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
// - Substring Search (string, array, kmp)
//   • When to use: Use when needing to find all occurrences or the first occurrence of a pattern string within a larger text string efficiently. It is particularly useful when the pattern might have significant self-overlapping prefixes and suffixes, allowing for linear time complexity.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently searches for occurrences of a pattern within a text by avoiding redundant comparisons. It preprocesses the pattern to build a Deterministic Finite Automaton (DFA) or Longest Proper Prefix Suffix (LPS) array, achieving O(N + M) time complexity.
//   • Invariants: During DFA construction, dfa[c][j] correctly stores the next state if character c is encountered in state j.; During DFA construction, x maintains the length of the longest proper prefix of pattern[0...j-1] that is also a suffix of pattern[0...j-1].
//   • Tips: Precompute the LPS array or DFA for the pattern to guide the search.; The LPS array indicates the longest proper prefix that is also a suffix, enabling efficient shifts.
//   • Pitfalls: Incorrect construction of the LPS array or DFA is a common source of errors.; High constant factors for small alphabets or short patterns might make simpler algorithms faster.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isMatch(char* s, char* p) {
    int m = strlen(s);
    int n = strlen(p);
    bool dp[m + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = true;

    for (int j = 1; j <= n; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2];
                if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        }
    }

    return dp[m][n];        
}
