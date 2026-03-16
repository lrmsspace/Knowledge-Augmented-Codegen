// Source: https://leetcode.com/problems/row-with-maximum-ones/   |   Difficulty: Easy
//
// Problem Description:
// Given a m x n binary matrix mat, find the 0-indexed position of the row that contains the maximum count of ones, and the number of ones in that row.
//
// In case there are multiple rows that have the maximum count of ones, the row with the smallest row number should be selected.
//
// Return an array containing the index of the row, and the number of ones in it.
//
// Example:
// Input: mat = [[0,1],[1,0]]
// Output: [0,1]
// Explanation: Both rows have the same number of 1's. So we return the index of the smaller row, 0, and the maximum count of ones (1). So, the answer is [0,1].
//
// Constraints:
// m == mat.length 
// 	n == mat[i].length 
// 	1 <= m, n <= 100 
// 	mat[i][j] is either 0 or 1.
//

/**
 * @param {number[][]} mat
 * @return {number[]}
 */
var rowAndMaximumOnes = function(mat) {
    let maxOnes = 0;
    let rowIndex = 0;
    for (let i = 0; i < mat.length; i++) {
        let countOnes = 0;
        for (let j = 0; j < mat[i].length; j++) {
            if (mat[i][j] === 1) {
                countOnes++;
            }
        }
        if (countOnes > maxOnes) {
            maxOnes = countOnes;
            rowIndex = i;
        }
    }
    return [rowIndex, maxOnes];
};