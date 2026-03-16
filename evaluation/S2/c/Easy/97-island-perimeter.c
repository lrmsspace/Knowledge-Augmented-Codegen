// Source: https://leetcode.com/problems/island-perimeter/   |   Difficulty: Easy
//
// Problem Description:
// You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
//
// Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
//
// The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.
//
// Example:
// Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
// Output: 16
// Explanation: The perimeter is the 16 yellow stripes in the image above.
//
// Constraints:
// row == grid.length
// 	col == grid[i].length
// 	1 <= row, col <= 100
// 	grid[i][j] is 0 or 1.
// 	There is exactly one island in grid.
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

int islandPerimeter(int** grid, int gridSize, int* gridColSize) {
    int perimeter = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == 1) {
                // Check the four directions
                perimeter += 4; // Start with 4 sides for each land cell

                // Check up
                if (i > 0 && grid[i - 1][j] == 1) {
                    perimeter -= 2; // Shared edge with upper cell
                }
                // Check down
                if (i < gridSize - 1 && grid[i + 1][j] == 1) {
                    perimeter -= 2; // Shared edge with lower cell
                }
                // Check left
                if (j > 0 && grid[i][j - 1] == 1) {
                    perimeter -= 2; // Shared edge with left cell
                }
                // Check right
                if (j < gridColSize[i] - 1 && grid[i][j + 1] == 1) {
                    perimeter -= 2; // Shared edge with right cell
                }
            }
        }
    }
    return perimeter;       
}
