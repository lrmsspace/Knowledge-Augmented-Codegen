// Source: https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer grid of size m x n and an integer x. In one operation, you can add x to or subtract x from any element in the grid.
//
// A uni-value grid is a grid where all the elements of it are equal.
//
// Return the minimum number of operations to make the grid uni-value. If it is not possible, return -1.
//
// Example:
// Input: grid = [[2,4],[6,8]], x = 2
// Output: 4
// Explanation: We can make every element equal to 4 by doing the following: 
// - Add x to 2 once.
// - Subtract x from 6 once.
// - Subtract x from 8 twice.
// A total of 4 operations were used.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	1 <= x, grid[i][j] <= 104
//

/**
 * @param {number[][]} grid
 * @param {number} x
 * @return {number}
 */
var minOperations = function(grid, x) {
    const flatGrid = [];
    for (const row of grid) {
        for (const val of row) {
            flatGrid.push(val);
        }
    }

    const remainder = flatGrid[0] % x;
    for (const val of flatGrid) {
        if (val % x !== remainder) {
            return -1;
        }
    }

    flatGrid.sort((a, b) => a - b);
    const median = flatGrid[Math.floor(flatGrid.length / 2)];
    let operations = 0;

    for (const val of flatGrid) {
        operations += Math.abs(val - median) / x;
    }

    return operations;
};