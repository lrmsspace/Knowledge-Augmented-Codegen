// Source: https://leetcode.com/problems/minimum-cost-good-caption/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string caption of length n. A good caption is a string where every character appears in groups of at least 3 consecutive occurrences.
//
// For example:
//
//
// 	"aaabbb" and "aaaaccc" are good captions.
// 	"aabbb" and "ccccd" are not good captions.
//
//
// You can perform the following operation any number of times:
//
// Choose an index i (where 0 <= i < n) and change the character at that index to either:
//
//
// 	The character immediately before it in the alphabet (if caption[i] != 'a').
// 	The character immediately after it in the alphabet (if caption[i] != 'z').
//
//
// Your task is to convert the given caption into a good caption using the minimum number of operations, and return it. If there are multiple possible good captions, return the lexicographically smallest one among them. If it is impossible to create a good caption, return an empty string "".
//
// Example:
// Input: caption = "cdcd"
//
// Output: "cccc"
//
// Explanation:
//
// It can be shown that the given caption cannot be transformed into a good caption with fewer than 2 operations. The possible good captions that can be created using exactly 2 operations are:
//
//
// 	"dddd": Change caption[0] and caption[2] to their next character 'd'.
// 	"cccc": Change caption[1] and caption[3] to their previous character 'c'.
//
//
// Since "cccc" is lexicographically smaller than "dddd", return "cccc".
//
// Constraints:
// 1 <= caption.length <= 5 * 104
// 	caption consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
// - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
//   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
//   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
//   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
//   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
//   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* minCostGoodCaption(char* caption) {
    int n = strlen(caption);
    int INF = 1e9;
    /* dp[i][c][k]: min cost to make caption[0..i] good, ending with char c repeated k times */
    int ***dp = (int***)malloc((n + 1) * sizeof(int**));
    for (int i = 0; i <= n; ++i) {
        dp[i] = (int**)malloc(26 * sizeof(int*));
        for (int c = 0; c < 26; ++c) {
            dp[i][c] = (int*)malloc(4 * sizeof(int));
            for (int k = 0; k < 4; ++k) dp[i][c][k] = INF;
        }
    }
    dp[0][0][0] = 0;

    for (int i = 0; i < n; ++i) {
        for (int c = 0; c < 26; ++c) {
            for (int k = 0; k < 4; ++k) {
                if (dp[i][c][k] == INF) continue;
                for (int nc = 0; nc < 26; ++nc) {
                    int cost = dp[i][c][k] + (caption[i] - 'a' != nc ? 1 : 0);
                    if (nc == c) {
                        int nk = k + 1;
                        if (nk > 3) nk = 3;
                        dp[i + 1][nc][nk] = (cost < dp[i + 1][nc][nk]) ? cost : dp[i + 1][nc][nk];
                    } else {
                        if (k >= 3) {
                            dp[i + 1][nc][1] = (cost < dp[i + 1][nc][1]) ? cost : dp[i + 1][nc][1];
                        }
                    }
                }
            }
        }
    }

    int minCost = INF;
    for (int c = 0; c < 26; ++c) {
        for (int k = 3; k <= 3; ++k) {
            if (dp[n][c][k] < minCost) minCost = dp[n][c][k];
        }
    }

    if (minCost == INF) {
        for (int i = 0; i <= n; ++i) {
            for (int c = 0; c < 26; ++c) {
                free(dp[i][c]);
            }
            free(dp[i]);
        }
        free(dp);
        return "";
    }
    /* Reconstruct the answer */
    char* result = (char*)malloc((n + 1) * sizeof(char));
    int i = n;
    int c = -1, k = -1;
    for (int cc = 0; cc < 26; ++cc) {
        for (int kk = 3; kk <= 3; ++kk) {
            if (dp[n][cc][kk] == minCost) {
                c = cc;
                k = kk;
                break;
            }
        }
        if (c != -1) break;
    }
    while (i > 0) {
        for (int pc = 0; pc < 26; ++pc) {
            for (int pk = 0; pk < 4; ++pk) {
                if (pc == c) {
                    int nk = pk + 1;
                    if (nk > 3) nk = 3;
                    if (nk == k) {
                        int cost = dp[i - 1][pc][pk] + (caption[i - 1] - 'a' != c ? 1 : 0);
                        if (cost == dp[i][c][k]) {
                            result[i - 1] = 'a' + c;
                            i--;
                            c = pc;
                            k = pk;
                            goto next;
                        }
                    }
                } else {
                    if (pk >= 3 && k == 1) {
                        int cost = dp[i - 1][pc][pk] + (caption[i - 1] - 'a' != c ? 1 : 0);
                        if (cost == dp[i][c][k]) {
                            result[i - 1] = 'a' + c;
                            i--;
                            c = pc;
                            k = pk;
                            goto next;
                        }
                    }
                }
            }
        }
    next:;
    }
    result[n] = '\0';
    for (int i = 0; i <= n; ++i) {
        for (int cc = 0; cc < 26; ++cc) {
            free(dp[i][cc]);
        }
        free(dp[i]);
    }
    free(dp);
    *returnSize = n;
    return result;
}
