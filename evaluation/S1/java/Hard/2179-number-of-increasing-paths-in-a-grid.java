// Source: https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer matrix grid, where you can move from a cell to any adjacent cell in all 4 directions.
//
// Return the number of strictly increasing paths in the grid such that you can start from any cell and end at any cell. Since the answer may be very large, return it modulo 109 + 7.
//
// Two paths are considered different if they do not have exactly the same sequence of visited cells.
//
// Example:
// Input: grid = [[1,1],[3,4]]
// Output: 8
// Explanation: The strictly increasing paths are:
// - Paths with length 1: [1], [1], [3], [4].
// - Paths with length 2: [1 -> 3], [1 -> 4], [3 -> 4].
// - Paths with length 3: [1 -> 3 -> 4].
// The total number of paths is 4 + 3 + 1 = 8.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	1 <= grid[i][j] <= 105
//
// Helpful references (internal KB):
// - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
//   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
//   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
//   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
//   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
//   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int countPaths(int[][] grid) {
        int MOD = 1_000_000_007;
        int m = grid.length;
        int n = grid[0].length;

        // Directions for moving up, down, left, right
        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // Memoization table
        Integer[][] memo = new Integer[m][n];

        // DFS function to count paths starting from (i, j)
        class DFS {
            int dfs(int i, int j) {
                if (memo[i][j] != null) {
                    return memo[i][j];
                }

                int count = 1; // Count the path that starts and ends at (i, j)

                for (int[] dir : directions) {
                    int ni = i + dir[0];
                    int nj = j + dir[1];

                    if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] > grid[i][j]) {
                        count = (count + dfs(ni, nj)) % MOD;
                    }
                }

                memo[i][j] = count;
                return count;
            }
        }

        DFS dfsSolver = new DFS();
        int totalPaths = 0;

        // Calculate paths starting from each cell
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                totalPaths = (totalPaths + dfsSolver.dfs(i, j)) % MOD;
            }
        }

        return totalPaths;          
    }
}
