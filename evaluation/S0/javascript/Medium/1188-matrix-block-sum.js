// Source: https://leetcode.com/problems/matrix-block-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given a m x n matrix mat and an integer k, return a matrix answer where each answer[i][j] is the sum of all elements mat[r][c] for:
//
//
// 	i - k <= r <= i + k,
// 	j - k <= c <= j + k, and
// 	(r, c) is a valid position in the matrix.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
// Output: [[12,21,16],[27,45,33],[24,39,28]]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n, k <= 100
// 	1 <= mat[i][j] <= 100
//

/**
 * @param {number[][]} mat
 * @param {number} k
 * @return {number[][]}
 */
var matrixBlockSum = function(mat, k) {
    
    const m = mat.length;
    const n = mat[0].length;
    const result = Array.from({ length: m }, () => Array(n).fill(0));

    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            for (let r = Math.max(0, i - k); r <= Math.min(m - 1, i + k); r++) {
                for (let c = Math.max(0, j - k); c <= Math.min(n - 1, j + k); c++) {
                    result[i][j] += mat[r][c];
                }
            }
        }
    }
    return result;
    
};
