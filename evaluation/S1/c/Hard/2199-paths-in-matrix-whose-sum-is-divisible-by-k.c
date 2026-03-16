// Source: https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed m x n integer matrix grid and an integer k. You are currently at position (0, 0) and you want to reach position (m - 1, n - 1) moving only down or right.
//
// Return the number of paths where the sum of the elements on the path is divisible by k. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
// Output: 2
// Explanation: There are two paths where the sum of the elements on the path is divisible by k.
// The first path highlighted in red has a sum of 5 + 2 + 4 + 5 + 2 = 18 which is divisible by 3.
// The second path highlighted in blue has a sum of 5 + 3 + 0 + 5 + 2 = 15 which is divisible by 3.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 5 * 104
// 	1 <= m * n <= 5 * 104
// 	0 <= grid[i][j] <= 100
// 	1 <= k <= 50
//
// Helpful references (internal KB):
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numberOfPaths(int** grid, int gridSize, int* gridColSize, int k) {
    const int MOD = 1000000007;
    int m = gridSize;
    int n = gridColSize[0];

    /* dp[j][r]: number of paths to (i,j) with sum % k == r */
    int dp[n][k];
    memset(dp, 0, sizeof(dp));

    /* Initialize for the first cell (0,0) */
    dp[0][grid[0][0] % k] = 1;

    /* Fill dp for the first row */
    for (int j = 1; j < n; j++) {
        for (int r = 0; r < k; r++) {
            int new_r = (r + grid[0][j]) % k;
            dp[j][new_r] = (dp[j][new_r] + dp[j - 1][r]) % MOD;
        }
    }

    /* Fill dp for the rest of the rows */
    for (int i = 1; i < m; i++) {
        /* Update first column of the current row */
        int new_dp[k];
        memset(new_dp, 0, sizeof(new_dp));
        for (int r = 0; r < k; r++) {
            int new_r = (r + grid[i][0]) % k;
            new_dp[new_r] = (new_dp[new_r] + dp[0][r]) % MOD;
        }
        memcpy(dp[0], new_dp, sizeof(new_dp));

        /* Update the rest of the columns */
        for (int j = 1; j < n; j++) {
            memset(new_dp, 0, sizeof(new_dp));
            for (int r = 0; r < k; r++) {
                int new_r = (r + grid[i][j]) % k;
                new_dp[new_r] = (new_dp[new_r] + dp[j][r]) % MOD;       /* from top */
                new_dp[new_r] = (new_dp[new_r] + dp[j - 1][r]) % MOD;   /* from left */
            }
            memcpy(dp[j], new_dp, sizeof(new_dp));
        }
    }

    return dp[n - 1][0];        
}
