// Source: https://leetcode.com/problems/surface-area-of-3d-shapes/   |   Difficulty: Easy
//
// Problem Description:
// You are given an n x n grid where you have placed some 1 x 1 x 1 cubes. Each value v = grid[i][j] represents a tower of v cubes placed on top of cell (i, j).
//
// After placing these cubes, you have decided to glue any directly adjacent cubes to each other, forming several irregular 3D shapes.
//
// Return the total surface area of the resulting shapes.
//
// Note: The bottom face of each shape counts toward its surface area.
//
// Example:
// Input: grid = [[1,2],[3,4]]
// Output: 34
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
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} grid
 * @return {number}
 */
var surfaceArea = function(grid) {
    const n = grid.length;
    let area = 0;
    
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] > 0) {
                // Each cube contributes 4 side surfaces and 2 top/bottom surfaces
                area += grid[i][j] * 4 + 2;
                
                // Subtract overlapping surfaces with adjacent cubes
                if (i > 0) {
                    area -= Math.min(grid[i][j], grid[i-1][j]) * 2;
                }
                if (j > 0) {
                    area -= Math.min(grid[i][j], grid[i][j-1]) * 2;
                }
            }
        }
    }
    
    return area;
};
