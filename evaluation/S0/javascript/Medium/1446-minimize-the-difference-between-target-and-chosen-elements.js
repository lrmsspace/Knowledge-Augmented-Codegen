// Source: https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix mat and an integer target.
//
// Choose one integer from each row in the matrix such that the absolute difference between target and the sum of the chosen elements is minimized.
//
// Return the minimum absolute difference.
//
// The absolute difference between two numbers a and b is the absolute value of a - b.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]], target = 13
// Output: 0
// Explanation: One possible choice is to:
// - Choose 1 from the first row.
// - Choose 5 from the second row.
// - Choose 7 from the third row.
// The sum of the chosen elements is 13, which equals the target, so the absolute difference is 0.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 70
// 	1 <= mat[i][j] <= 70
// 	1 <= target <= 800
//

/**
 * @param {number[][]} mat
 * @param {number} target
 * @return {number}
 */
var minimizeTheDifference = function(mat, target) {
    const m = mat.length;
    const possibleSums = new Set();
    possibleSums.add(0);
    for (let i = 0; i < m; i++) {
        const currentRow = mat[i];
        const newPossibleSums = new Set();
        for (const sum of possibleSums) {
            for (const num of currentRow) {
                newPossibleSums.add(sum + num);
            }
        }
        possibleSums.clear();
    }
    let minDiff = Infinity;
    for (const sum of possibleSums) {
        minDiff = Math.min(minDiff, Math.abs(sum - target));
    }
    return minDiff;
};
