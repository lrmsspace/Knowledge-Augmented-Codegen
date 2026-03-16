// Source: https://leetcode.com/problems/projection-area-of-3d-shapes/   |   Difficulty: Easy
//
// Problem Description:
// You are given an n x n grid where we place some 1 x 1 x 1 cubes that are axis-aligned with the x, y, and z axes.
//
// Each value v = grid[i][j] represents a tower of v cubes placed on top of the cell (i, j).
//
// We view the projection of these cubes onto the xy, yz, and zx planes.
//
// A projection is like a shadow, that maps our 3-dimensional figure to a 2-dimensional plane. We are viewing the "shadow" when looking at the cubes from the top, the front, and the side.
//
// Return the total area of all three projections.
//
// Example:
// Input: grid = [[1,2],[3,4]]
// Output: 17
// Explanation: Here are the three projections ("shadows") of the shape made with each axis-aligned plane.
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 50
// 	0 <= grid[i][j] <= 50
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

int projectionArea(int** grid, int gridSize, int* gridColSize) {
    int xy = 0, yz = 0, zx = 0;
    for (int i = 0; i < gridSize; i++) {
        int maxRow = 0;
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] > 0) {
                xy++;
            }
            if (grid[i][j] > maxRow) {
                maxRow = grid[i][j];
            }
            if (grid[j][i] > yz) {
                yz = grid[j][i];
            }
        }
        zx += maxRow;
    }
    return xy + yz + zx;        
}
