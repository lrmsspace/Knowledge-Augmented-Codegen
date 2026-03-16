// Source: https://leetcode.com/problems/largest-submatrix-with-rearrangements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns of the matrix in any order.
//
// Return the area of the largest submatrix within matrix where every element of the submatrix is 1 after reordering the columns optimally.
//
// Example:
// Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
// Output: 4
// Explanation: You can rearrange the columns as shown above.
// The largest submatrix of 1s, in bold, has an area of 4.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m * n <= 105
// 	matrix[i][j] is either 0 or 1.
//

/**
 * @param {number[][]} matrix
 * @return {number}
 */
var largestSubmatrix = function(matrix) {
    const m = matrix.length;
    const n = matrix[0].length;
    const heights = Array.from({ length: m }, () => Array(n).fill(0));
    for (let j = 0; j < n; j++) {
        for (let i = 0; i < m; i++) {
            if (matrix[i][j] === 1) {
                heights[i][j] = (i > 0 ? heights[i - 1][j] : 0) + 1;
            }
        }
    }
    let maxArea = 0;
    for (let i = 0; i < m; i++) {
        const sortedHeights = [...heights[i]].sort((a, b) => b - a);
        for (let j = 0; j < n; j++) {
            const area = sortedHeights[j] * (j + 1);
            maxArea = Math.max(maxArea, area);
        }
    }
    return maxArea;
};
