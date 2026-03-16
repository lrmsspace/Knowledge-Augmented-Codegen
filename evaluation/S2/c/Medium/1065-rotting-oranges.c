// Source: https://leetcode.com/problems/rotting-oranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n grid where each cell can have one of three values:
//
//
// 	0 representing an empty cell,
// 	1 representing a fresh orange, or
// 	2 representing a rotten orange.
//
//
// Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
//
// Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.
//
// Example:
// Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
// Output: 4
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 10
// 	grid[i][j] is 0, 1, or 2.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int orangesRotting(int** grid, int gridSize, int* gridColSize) {
    if (gridSize == 0 || gridColSize[0] == 0) {
        return -1; // No oranges
    }

    int rows = gridSize;
    int cols = gridColSize[0];
    int freshCount = 0;
    int rottenCount = 0;

    // Count fresh and rotten oranges
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                freshCount++;
            } else if (grid[i][j] == 2) {
                rottenCount++;
            }
        }
    }

    if (freshCount == 0) {
        return 0; // No fresh oranges to rot
    }

    int minutes = 0;
    while (rottenCount > 0) {
        int newRottenCount = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 2) { // Rotten orange
                    // Check adjacent cells
                    if (i > 0 && grid[i - 1][j] == 1) { // Up
                        grid[i - 1][j] = 2;
                        freshCount--;
                        newRottenCount++;
                    }
                    if (i < rows - 1 && grid[i + 1][j] == 1) { // Down
                        grid[i + 1][j] = 2;
                        freshCount--;
                        newRottenCount++;
                    }
                    if (j > 0 && grid[i][j - 1] == 1) { // Left
                        grid[i][j - 1] = 2;
                        freshCount--;
                        newRottenCount++;
                    }
                    if (j < cols - 1 && grid[i][j + 1] == 1) { // Right
                        grid[i][j + 1] = 2;
                        freshCount--;
                        newRottenCount++;
                    }
                }
            }
        }

        if (newRottenCount == 0) {
            break; // No new oranges rotted, stop the process
        }

        rottenCount += newRottenCount;
        minutes++;      

}
    
    return freshCount == 0 ? minutes : -1; // If there are still fresh oranges, return -1
}