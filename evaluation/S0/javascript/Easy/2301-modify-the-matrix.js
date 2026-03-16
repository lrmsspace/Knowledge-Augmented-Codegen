// Source: https://leetcode.com/problems/modify-the-matrix/   |   Difficulty: Easy
//
// Problem Description:
// Given a 0-indexed m x n integer matrix matrix, create a new 0-indexed matrix called answer. Make answer equal to matrix, then replace each element with the value -1 with the maximum element in its respective column.
//
// Return the matrix answer.
//
// Example:
// Input: matrix = [[1,2,-1],[4,-1,6],[7,8,9]]
// Output: [[1,2,9],[4,8,6],[7,8,9]]
// Explanation: The diagram above shows the elements that are changed (in blue).
// - We replace the value in the cell [1][1] with the maximum value in the column 1, that is 8.
// - We replace the value in the cell [0][2] with the maximum value in the column 2, that is 9.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	2 <= m, n <= 50
// 	-1 <= matrix[i][j] <= 100
// 	The input is generated such that each column contains at least one non-negative integer.
//

/**
 * @param {number[][]} matrix
 * @return {number[][]}
 */
var modifiedMatrix = function(matrix) {
    const m = matrix.length;
    const n = matrix[0].length;
    const result = Array.from({ length: m }, () => Array(n).fill(0));
    const maxInColumn = Array(n).fill(-Infinity);

    for (let j = 0; j < n; j++) {
        for (let i = 0; i < m; i++) {
            if (matrix[i][j] !== -1) {
                maxInColumn[j] = Math.max(maxInColumn[j], matrix[i][j]);
            }
        }
    }

    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (matrix[i][j] === -1) {
                result[i][j] = maxInColumn[j];
            } else {
                result[i][j] = matrix[i][j];
            }
        }
    }

    return result;
};