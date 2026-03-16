// Source: https://leetcode.com/problems/minimum-number-of-operations-to-satisfy-conditions/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D matrix grid of size m x n. In one operation, you can change the value of any cell to any non-negative number. You need to perform some operations such that each cell grid[i][j] is:
//
//
// 	Equal to the cell below it, i.e. grid[i][j] == grid[i + 1][j] (if it exists).
// 	Different from the cell to its right, i.e. grid[i][j] != grid[i][j + 1] (if it exists).
//
//
// Return the minimum number of operations needed.
//
// Example:
// Input: grid = [[1,0,2],[1,0,2]]
//
// Output: 0
//
// Explanation:
//
//
//
// All the cells in the matrix already satisfy the properties.
//
// Constraints:
// 1 <= n, m <= 1000
// 	0 <= grid[i][j] <= 9
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var minimumOperations = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    let operations = 0;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (i < m - 1 && grid[i][j] !== grid[i + 1][j]) {
                operations++;
            }
            if (j < n - 1 && grid[i][j] === grid[i][j + 1]) {
                operations++;
            }
        }
    }
    return operations;
};
