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

/**
 * @param {number[][]} grid
 * @return {number}
 */
var surfaceArea = function(grid) {
    const n = grid.length;
    let area = 0;
    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] > 0) {
                area += 2; // Top and bottom faces
                for (const [dx, dy] of directions) {
                    const ni = i + dx;
                    const nj = j + dy;
                    const neighborHeight = (ni >= 0 && ni < n && nj >= 0 && nj < n) ? grid[ni][nj] : 0;
                    area += Math.max(0, grid[i][j] - neighborHeight);
                }
            }
        }
    }
    return area;
};
