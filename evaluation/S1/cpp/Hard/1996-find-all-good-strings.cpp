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
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int findGoodStrings(int n, string s1, string s2, string evil) {
        const int MOD = 1e9 + 7;

        // KMP to build the longest prefix-suffix (LPS) array for 'evil'
        vector<int> lps(evil.size(), 0);
        for (int i = 1, len = 0; i < evil.size(); ) {
            if (evil[i] == evil[len]) {
                lps[i++] = ++len;
            } else if (len) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }

        // DP memoization table
        vector<vector<vector<vector<int>>>> dp(
            n + 1, vector<vector<vector<int>>>(
                2, vector<vector<int>>(
                    2, vector<int>(evil.size(), -1))));

        function<int(int, int, int, int)> dfs = [&](int pos, int isPrefixS1, int isPrefixS2, int evilMatched) -> int {
            if (evilMatched == evil.size()) return 0; // 'evil' found
            if (pos == n) return 1; // valid string formed

            if (dp[pos][isPrefixS1][isPrefixS2][evilMatched] != -1) {
                return dp[pos][isPrefixS1][isPrefixS2][evilMatched];
            }

            char fromChar = isPrefixS1 ? s1[pos] : 'a';
            char toChar = isPrefixS2 ? s2[pos] : 'z';
            int totalWays = 0;

            for (char ch = fromChar; ch <= toChar; ++ch) {
                int nextEvilMatched = evilMatched;
                while (nextEvilMatched > 0 && ch != evil[nextEvilMatched]) {
                    nextEvilMatched = lps[nextEvilMatched - 1];
                }
                if (ch == evil[nextEvilMatched]) {
                    nextEvilMatched++;
                }

                totalWays = (totalWays + dfs(
                    pos + 1,
                    isPrefixS1 && (ch == fromChar),
                    isPrefixS2 && (ch == toChar),
                    nextEvilMatched)) % MOD;
            }

            return dp[pos][isPrefixS1][isPrefixS2][evilMatched] = totalWays;
        };

        return dfs(0, 1, 1, 0);
    }
};
