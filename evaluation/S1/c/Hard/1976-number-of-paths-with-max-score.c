// Source: https://leetcode.com/problems/number-of-paths-with-max-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given a square board of characters. You can move on the board starting at the bottom right square marked with the character 'S'.
//
// You need to reach the top left square marked with the character 'E'. The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.
//
// Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.
//
// In case there is no path, return [0, 0].
//
// Example:
// Input: board = ["E23","2X2","12S"]
// Output: [7,1]
//
// Constraints:
// 2 <= board.length == board[i].length <= 100
//
// Helpful references (internal KB):
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.



/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* pathsWithMaxScore(char ** board, int boardSize, int* returnSize){
    int MOD = 1000000007;
    int n = boardSize;
    int m = strlen(board[0]);
    int dpSum[n][m];
    int dpCount[n][m];
    memset(dpSum, 0, sizeof(dpSum));
    memset(dpCount, 0, sizeof(dpCount));
    dpCount[n-1][m-1] = 1; // Start at 'S'
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (board[i][j] == 'X' || (i == n - 1 && j == m - 1)) continue; // Obstacle or start
            int maxPrevSum = -1;
            int pathCount = 0;
            // Check down
            if (i + 1 < n && dpCount[i + 1][j] > 0) {
                if (dpSum[i + 1][j] > maxPrevSum) {
                    maxPrevSum = dpSum[i + 1][j];
                    pathCount = dpCount[i + 1][j];
                } else if (dpSum[i + 1][j] == maxPrevSum) {
                    pathCount = (pathCount + dpCount[i + 1][j]) % MOD;
                }
            }
            // Check right
            if (j + 1 < m && dpCount[i][j + 1] > 0) {
                if (dpSum[i][j + 1] > maxPrevSum) {
                    maxPrevSum = dpSum[i][j + 1];
                    pathCount = dpCount[i][j + 1];
                } else if (dpSum[i][j + 1] == maxPrevSum) {
                    pathCount = (pathCount + dpCount[i][j + 1]) % MOD;
                }
            }
            // Check down-right
            if (i + 1 < n && j + 1 < m && dpCount[i + 1][j + 1] > 0) {
                if (dpSum[i + 1][j + 1] > maxPrevSum) {
                    maxPrevSum = dpSum[i + 1][j + 1];
                    pathCount = dpCount[i + 1][j + 1];
                } else if (dpSum[i + 1][j + 1] == maxPrevSum) {
                    pathCount = (pathCount + dpCount[i + 1][j + 1]) % MOD;
                }
            }
            if (maxPrevSum != -1) {
                dpSum[i][j] = maxPrevSum + (board[i][j] >= '0' && board[i][j] <= '9' ? board[i][j] - '0' : 0);
                dpCount[i][j] = pathCount;
            }
        }
    }
    int* result = (int*)malloc(2 * sizeof(int));
    if (dpCount[0][0] == 0) {
        result[0] = 0;
        result[1] = 0;
    } else {
        result[0] = dpSum[0][0];
        result[1] = dpCount[0][0];
    }
    *returnSize = 2;
    return result;
}
