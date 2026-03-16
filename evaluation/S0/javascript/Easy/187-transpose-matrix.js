// Source: https://leetcode.com/problems/transpose-matrix/   |   Difficulty: Easy
//
// Problem Description:
// Given a 2D integer array matrix, return the transpose of matrix.
//
// The transpose of a matrix is the matrix flipped over its main diagonal, switching the matrix's row and column indices.
//
// Example:
// Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [[1,4,7],[2,5,8],[3,6,9]]
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	-109 <= matrix[i][j] <= 109
//

/**
 * @param {number[][]} matrix
 * @return {number[][]}
 */
var transpose = function(matrix) {
    const m = matrix.length;
    const n = matrix[0].length;
    const transposed = Array.from({ length: n }, () => new Array(m));
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
};