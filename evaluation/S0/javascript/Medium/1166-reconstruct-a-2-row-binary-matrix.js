// Source: https://leetcode.com/problems/reconstruct-a-2-row-binary-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given the following details of a matrix with n columns and 2 rows :
//
//
// 	The matrix is a binary matrix, which means each element in the matrix can be 0 or 1.
// 	The sum of elements of the 0-th(upper) row is given as upper.
// 	The sum of elements of the 1-st(lower) row is given as lower.
// 	The sum of elements in the i-th column(0-indexed) is colsum[i], where colsum is given as an integer array with length n.
//
//
// Your task is to reconstruct the matrix with upper, lower and colsum.
//
// Return it as a 2-D integer array.
//
// If there are more than one valid solution, any of them will be accepted.
//
// If no valid solution exists, return an empty 2-D array.
//
// Example:
// Input: upper = 2, lower = 1, colsum = [1,1,1]
// Output: [[1,1,0],[0,0,1]]
// Explanation: [[1,0,1],[0,1,0]], and [[0,1,1],[1,0,0]] are also correct answers.
//
// Constraints:
// 1 <= colsum.length <= 10^5
// 	0 <= upper, lower <= colsum.length
// 	0 <= colsum[i] <= 2
//

/**
 * @param {number} upper
 * @param {number} lower
 * @param {number[]} colsum
 * @return {number[][]}
 */
var reconstructMatrix = function(upper, lower, colsum) {
    const n = colsum.length;
    const result = Array.from({ length: 2 }, () => Array(n).fill(0));
    for (let i = 0; i < n; i++) {
        if (colsum[i] === 2) {
            result[0][i] = 1;
            result[1][i] = 1;
            upper--;
            lower--;
        } else if (colsum[i] === 1) {
            if (upper >= lower) {
                result[0][i] = 1;
                upper--;
            } else {
                result[1][i] = 1;
                lower--;
            }
        }
        if (upper < 0 || lower < 0) {
            return [];
        }
    }   
    if (upper !== 0 || lower !== 0) {
        return [];
    }
    return result;  
                
};
