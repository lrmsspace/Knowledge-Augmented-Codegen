// Source: https://leetcode.com/problems/count-submatrices-with-all-ones/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n binary matrix mat, return the number of submatrices that have all ones.
//
// Example:
// Input: mat = [[1,0,1],[1,1,0],[1,1,0]]
// Output: 13
// Explanation: 
// There are 6 rectangles of side 1x1.
// There are 2 rectangles of side 1x2.
// There are 3 rectangles of side 2x1.
// There is 1 rectangle of side 2x2. 
// There is 1 rectangle of side 3x1.
// Total number of rectangles = 6 + 2 + 3 + 1 + 1 = 13.
//
// Constraints:
// 1 <= m, n <= 150
// 	mat[i][j] is either 0 or 1.
//

/**
 * @param {number[][]} mat
 * @return {number}
 */
var numSubmat = function(mat) {
    const m = mat.length;
    const n = mat[0].length;
    let totalCount = 0;
    const height = Array(n).fill(0);
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (mat[i][j] === 1) {
                height[j]++;
            } else {
                height[j] = 0;
            }
        }
        for (let j = 0; j < n; j++) {
            let minHeight = height[j];
            for (let k = j; k >= 0; k--) {
                minHeight = Math.min(minHeight, height[k]);
                if (minHeight === 0) break;
                totalCount += minHeight;
            }
        }
    }
    return totalCount;  
};
