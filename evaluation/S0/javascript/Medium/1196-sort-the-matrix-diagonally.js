// Source: https://leetcode.com/problems/sort-the-matrix-diagonally/   |   Difficulty: Medium
//
// Problem Description:
// A matrix diagonal is a diagonal line of cells starting from some cell in either the topmost row or leftmost column and going in the bottom-right direction until reaching the matrix's end. For example, the matrix diagonal starting from mat[2][0], where mat is a 6 x 3 matrix, includes cells mat[2][0], mat[3][1], and mat[4][2].
//
// Given an m x n matrix mat of integers, sort each matrix diagonal in ascending order and return the resulting matrix.
//
// Example:
// Input: mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
// Output: [[1,1,1,1],[1,2,2,2],[1,2,3,3]]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 100
// 	1 <= mat[i][j] <= 100
//

/**
 * @param {number[][]} mat
 * @return {number[][]}
 */
var diagonalSort = function(mat) {
    const m = mat.length;
    const n = mat[0].length;
    const diagonals = {};
    // Collect elements of each diagonal
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            const key = i - j;
            if (!diagonals[key]) {
                diagonals[key] = [];
            }
            diagonals[key].push(mat[i][j]);
        }
    }
    // Sort each diagonal
    for (const key in diagonals) {
        diagonals[key].sort((a, b) => a - b);
    }
    // Place sorted elements back into the matrix
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            const key = i - j;
            mat[i][j] = diagonals[key].shift();
        }
    }
    return mat;
        
};
