// Source: https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/   |   Difficulty: Medium
//
// Problem Description:
// Given a m x n matrix mat and an integer threshold, return the maximum side-length of a square with a sum less than or equal to threshold or return 0 if there is no such square.
//
// Example:
// Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
// Output: 2
// Explanation: The maximum side length of square with sum less than 4 is 2 as shown.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 300
// 	0 <= mat[i][j] <= 104
// 	0 <= threshold <= 105
//

/**
 * @param {number[][]} mat
 * @param {number} threshold
 * @return {number}
 */
var maxSideLength = function(mat, threshold) {
    const m = mat.length;
    const n = mat[0].length;
    const prefixSum = Array.from({ length: m + 1 }, () => Array(n + 1).fill(0));
    let maxSide = 0;
    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            prefixSum[i][j] = mat[i - 1][j - 1] + prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
            for (let side = maxSide + 1; side <= Math.min(i, j); side++) {
                const total = prefixSum[i][j] - prefixSum[i - side][j] - prefixSum[i][j - side] + prefixSum[i - side][j - side];
                if (total <= threshold) {
                    maxSide = side;
                } else {
                    break;
                }
            }
        }
    }
    return maxSide;
        
};
