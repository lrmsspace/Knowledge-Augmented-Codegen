// Source: https://leetcode.com/problems/check-if-grid-satisfies-conditions/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 2D matrix grid of size m x n. You need to check if each cell grid[i][j] is:
//
//
// 	Equal to the cell below it, i.e. grid[i][j] == grid[i + 1][j] (if it exists).
// 	Different from the cell to its right, i.e. grid[i][j] != grid[i][j + 1] (if it exists).
//
//
// Return true if all the cells satisfy these conditions, otherwise, return false.
//
// Example:
// Input: grid = [[1,0,2],[1,0,2]]
//
// Output: true
//
// Explanation:
//
//
//
// All the cells in the grid satisfy the conditions.
//
// Constraints:
// 1 <= n, m <= 10
// 	0 <= grid[i][j] <= 9
//

/**
 * @param {number[][]} grid
 * @return {boolean}
 */
var satisfiesConditions = function(grid) {
    const rows = grid.length;
    const cols = grid[0].length;
    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            if (i + 1 < rows && grid[i][j] !== grid[i + 1][j]) {
                return false;
            }
            if (j + 1 < cols && grid[i][j] === grid[i][j + 1]) {
                return false;
            }
        }
    }
    return true;
};