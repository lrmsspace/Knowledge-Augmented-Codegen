// Source: https://leetcode.com/problems/diagonal-traverse/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,2,4,7,5,3,6,8,9]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 104
// 	1 <= m * n <= 104
// 	-105 <= mat[i][j] <= 105
//

/**
 * @param {number[][]} mat
 * @return {number[]}
 */
var findDiagonalOrder = function(mat) {
    const m = mat.length;
    const n = mat[0].length;
    const result = [];
    let row = 0, col = 0;
    let direction = 1; // 1 for up-right, -1 for down-left
    while (result.length < m * n) {
        result.push(mat[row][col]);
        if (direction === 1) { // moving up-right
            if (col === n - 1) {
                row++;
                direction = -1;
            } else if (row === 0) {
                col++;
                direction = -1;
            } else {
                row--;
                col++;
            }
        } else { // moving down-left
            if (row === m - 1) {
                col++;
                direction = 1;
            } else if (col === 0) {
                row++;
                direction = 1;
            } else {
                row++;
                col--;
            }
        }
    }
    return result;
};