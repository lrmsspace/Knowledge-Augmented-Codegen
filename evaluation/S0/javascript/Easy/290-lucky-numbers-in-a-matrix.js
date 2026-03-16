// Source: https://leetcode.com/problems/lucky-numbers-in-a-matrix/   |   Difficulty: Easy
//
// Problem Description:
// Given an m x n matrix of distinct numbers, return all lucky numbers in the matrix in any order.
//
// A lucky number is an element of the matrix such that it is the minimum element in its row and maximum in its column.
//
// Example:
// Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
// Output: [15]
// Explanation: 15 is the only lucky number since it is the minimum in its row and the maximum in its column.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= n, m <= 50
// 	1 <= matrix[i][j] <= 105.
// 	All elements in the matrix are distinct.
//

/**
 * @param {number[][]} matrix
 * @return {number[]}
 */
var luckyNumbers = function(matrix) {
    const luckyNumbers = [];
    const numRows = matrix.length;
    const numCols = matrix[0].length;
    for (let i = 0; i < numRows; i++) {
        let minColIndex = 0;
        for (let j = 1; j < numCols; j++) {
            if (matrix[i][j] < matrix[i][minColIndex]) {
                minColIndex = j;
            }
        }
        let isLucky = true; 
        for (let k = 0; k < numRows; k++) {
            if (matrix[k][minColIndex] > matrix[i][minColIndex]) {
                isLucky = false;
                break;
            }
        }
        if (isLucky) {
            luckyNumbers.push(matrix[i][minColIndex]);
        }   
    }
    return luckyNumbers;    
};
