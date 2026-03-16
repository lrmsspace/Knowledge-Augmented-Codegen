// Source: https://leetcode.com/problems/special-positions-in-a-binary-matrix/   |   Difficulty: Easy
//
// Problem Description:
// Given an m x n binary matrix mat, return the number of special positions in mat.
//
// A position (i, j) is called special if mat[i][j] == 1 and all other elements in row i and column j are 0 (rows and columns are 0-indexed).
//
// Example:
// Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
// Output: 1
// Explanation: (1, 2) is a special position because mat[1][2] == 1 and all other elements in row 1 and column 2 are 0.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 100
// 	mat[i][j] is either 0 or 1.
//

/**
 * @param {number[][]} mat
 * @return {number}
 */
var numSpecial = function(mat) {
    const m = mat.length;
    const n = mat[0].length;
    let specialCount = 0;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (mat[i][j] === 1) {
                let isSpecial = true;
                for (let k = 0; k < m; k++) {
                    if (k !== i && mat[k][j] === 1) {
                        isSpecial = false;
                        break;
                    }
                }
                for (let l = 0; l < n; l++) {
                    if (l !== j && mat[i][l] === 1) {
                        isSpecial = false;
                        break;
                    }
                }
                if (isSpecial) {
                    specialCount++;
                }
            }
        }
    }
    return specialCount;
};