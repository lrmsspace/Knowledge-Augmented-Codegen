// Source: https://leetcode.com/problems/find-number-of-ways-to-reach-the-k-th-stair/   |   Difficulty: Hard
//
// Problem Description:
// You are given a non-negative integer k. There exists a staircase with an infinite number of stairs, with the lowest stair numbered 0.
//
// Alice has an integer jump, with an initial value of 0. She starts on stair 1 and wants to reach stair k using any number of operations. If she is on stair i, in one operation she can:
//
//
// 	Go down to stair i - 1. This operation cannot be used consecutively or on stair 0.
// 	Go up to stair i + 2jump. And then, jump becomes jump + 1.
//
//
// Return the total number of ways Alice can reach stair k.
//
// Note that it is possible that Alice reaches the stair k, and performs some operations to reach the stair k again.
//
// Example:
// Input: k = 0
//
// Output: 2
//
// Explanation:
//
// The 2 possible ways of reaching stair 0 are:
//
//
// 	Alice starts at stair 1.
// 	
// 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
// 	
// 	
// 	Alice starts at stair 1.
// 	
// 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
// 		Using an operation of the second type, she goes up 20 stairs to reach stair 1.
// 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
//
// Constraints:
// 0 <= k <= 109
//
// Helpful references (internal KB):
// - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
//   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
//   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
//   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
//   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
//   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int waysToReachStair(int k) {
        long MOD = 1_000_000_007L;

        // Find the maximum n such that n * (n + 1) / 2 <= k + 1
        long left = 0, right = (long) 2e9;
        while (left < right) {
            long mid = left + (right - left + 1) / 2;
            if (mid * (mid + 1) / 2 <= k + 1) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        int n = (int) left;

        // dp[i][j]: number of ways to reach stair j using first i jumps
        long[][] dp = new long[n + 1][k + 2];
        dp[0][1] = 1; // Starting at stair 1 with jump 0

        for (int i = 1; i <= n; i++) {
            int jumpSize = 2 * i - 2; // Size of the jump for jump i-1
            for (int j = 0; j <= k + 1; j++) {
                // Option 1: Go up to stair j + jumpSize
                if (j + jumpSize <= k + 1) {
                    dp[i][j + jumpSize] = (dp[i][j + jumpSize] + dp[i - 1][j]) % MOD;
                }
                // Option 2: Go down to stair j - 1
                if (j - 1 >= 0) {
                    dp[i][j - 1] = (dp[i][j - 1] + dp[i][j]) % MOD;
                }
            }
        }

        return (int) dp[n][k];          
    }
}
