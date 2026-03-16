// Source: https://leetcode.com/problems/shift-2d-grid/   |   Difficulty: Easy
//
// Problem Description:
// Given a 2D grid of size m x n and an integer k. You need to shift the grid k times.
//
// In one shift operation:
//
//
// 	Element at grid[i][j] moves to grid[i][j + 1].
// 	Element at grid[i][n - 1] moves to grid[i + 1][0].
// 	Element at grid[m - 1][n - 1] moves to grid[0][0].
//
//
// Return the 2D grid after applying shift operation k times.
//
// Example:
// Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
// Output: [[9,1,2],[3,4,5],[6,7,8]]
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m <= 50
// 	1 <= n <= 50
// 	-1000 <= grid[i][j] <= 1000
// 	0 <= k <= 100
//

/**
 * @param {number[][]} grid
 * @param {number} k
 * @return {number[][]}
 */
var shiftGrid = function(grid, k) {
    const m = grid.length;
    const n = grid[0].length;
    const totalCells = m * n;
    k = k % totalCells;  
    const result = Array.from({ length: m }, () => new Array(n).fill(0));
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            const newIndex = (i * n + j + k) % totalCells;
            const newRow = Math.floor(newIndex / n);
            const newCol = newIndex % n;
            result[newRow][newCol] = grid[i][j];
        }
    }
    return result;
};