// Source: https://leetcode.com/problems/find-all-good-strings/   |   Difficulty: Hard
//
// Problem Description:
// Given the strings s1 and s2 of size n and the string evil, return the number of good strings.
//
// A good string has size n, it is alphabetically greater than or equal to s1, it is alphabetically smaller than or equal to s2, and it does not contain the string evil as a substring. Since the answer can be a huge number, return this modulo 109 + 7.
//
// Example:
// Input: n = 2, s1 = "aa", s2 = "da", evil = "b"
// Output: 51 
// Explanation: There are 25 good strings starting with 'a': "aa","ac","ad",...,"az". Then there are 25 good strings starting with 'c': "ca","cc","cd",...,"cz" and finally there is one good string starting with 'd': "da".
//
// Constraints:
// s1.length == n
// 	s2.length == n
// 	s1 <= s2
// 	1 <= n <= 500
// 	1 <= evil.length <= 50
// 	All strings consist of lowercase English letters.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int dfs(int index, int evilIndex, int limitFlag, int n, String s1, String s2, String evil, int[] lps, Integer[][][] memo, final int MOD) {
        if (evilIndex == evil.length()) {
            return 0; // Found evil substring
        }
        if (index == n) {
            return 1; // Valid good string
        }
        if (memo[index][evilIndex][limitFlag] != null) {
            return memo[index][evilIndex][limitFlag];
        }

        char fromChar = (limitFlag & 1) != 0 ? s1.charAt(index) : 'a';
        char toChar = (limitFlag & 2) != 0 ? s2.charAt(index) : 'z';

        int totalWays = 0;
        for (char c = fromChar; c <= toChar; c++) {
            int newLimitFlag = limitFlag;
            if (c > fromChar) {
                newLimitFlag &= ~1; // No longer limited by s1
            }
            if (c < toChar) {
                newLimitFlag &= ~2; // No longer limited by s2
            }

            // Update evilIndex using KMP logic
            int nextEvilIndex = evilIndex;
            while (nextEvilIndex > 0 && c != evil.charAt(nextEvilIndex)) {
                nextEvilIndex = lps[nextEvilIndex - 1];
            }
            if (c == evil.charAt(nextEvilIndex)) {
                nextEvilIndex++;
            }

            totalWays = (totalWays + dfs(index + 1, nextEvilIndex, newLimitFlag, n, s1, s2, evil, lps, memo, MOD)) % MOD;
        }

        memo[index][evilIndex][limitFlag] = totalWays;
        return totalWays;
    }
    public int findGoodStrings(int n, String s1, String s2, String evil) {
        final int MOD = 1_000_000_007;
        int m = evil.length();

        // Build KMP longest prefix-suffix (LPS) array for the evil string
        int[] lps = new int[m];
        for (int i = 1, len = 0; i < m; ) {
            if (evil.charAt(i) == evil.charAt(len)) {
                lps[i++] = ++len;
            } else if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }

        // DP memoization table
        Integer[][][] memo = new Integer[n + 1][m + 1][4];

        // Recursive DP function
        return dfs(0, 0, 3, n, s1, s2, evil, lps, memo, MOD);           
    }
}
