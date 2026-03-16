// Source: https://leetcode.com/problems/find-the-width-of-columns-of-a-grid/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed m x n integer matrix grid. The width of a column is the maximum length of its integers.
//
//
// 	For example, if grid = [[-10], [3], [12]], the width of the only column is 3 since -10 is of length 3.
//
//
// Return an integer array ans of size n where ans[i] is the width of the ith column.
//
// The length of an integer x with len digits is equal to len if x is non-negative, and len + 1 otherwise.
//
// Example:
// Input: grid = [[1],[22],[333]]
// Output: [3]
// Explanation: In the 0th column, 333 is of length 3.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 100 
// 	-109 <= grid[r][c] <= 109
//

/**
 * @param {number[][]} grid
 * @return {number[]}
 */
var findColumnWidth = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const result = new Array(n).fill(0);
    for (let j = 0; j < n; j++) {
        let maxWidth = 0;
        for (let i = 0; i < m; i++) {
            const length = grid[i][j].toString().length;
            maxWidth = Math.max(maxWidth, length);
        }
        result[j] = maxWidth;
    }
    return result;
};