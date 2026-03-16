// Source: https://leetcode.com/problems/unique-paths-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer array grid where grid[i][j] could be:
//
//
// 	1 representing the starting square. There is exactly one starting square.
// 	2 representing the ending square. There is exactly one ending square.
// 	0 representing empty squares we can walk over.
// 	-1 representing obstacles that we cannot walk over.
//
//
// Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.
//
// Example:
// Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
// Output: 2
// Explanation: We have the following two paths: 
// 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
// 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 20
// 	1 <= m * n <= 20
// 	-1 <= grid[i][j] <= 2
// 	There is exactly one starting cell and one ending cell.
//
// Helpful references (internal KB):
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int uniquePathsIII(int** grid, int gridSize, int* gridColSize) {
    int emptyCount = 0, startX = 0, startY = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == 1) {
                startX = i;
                startY = j;
            } else if (grid[i][j] == 0) {
                emptyCount++;
            }
        }
    }

    int pathCount = 0;
    void dfs(int x, int y, int count) {
        if (x < 0 || x >= gridSize || y < 0 || y >= gridColSize[x] || grid[x][y] == -1) {
            return;
        }
        if (grid[x][y] == 2) {
            if (count == emptyCount + 1) {
                pathCount++;
            }
            return;
        }

        grid[x][y] = -1; // Mark as visited
        dfs(x + 1, y, count + 1);
        dfs(x - 1, y, count + 1);
        dfs(x, y + 1, count + 1);
        dfs(x, y - 1, count + 1);
        grid[x][y] = 0; // Backtrack
    }

    dfs(startX, startY, 0);
    return pathCount;       
}
