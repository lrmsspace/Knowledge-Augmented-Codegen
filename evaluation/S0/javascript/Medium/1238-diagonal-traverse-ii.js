// Source: https://leetcode.com/problems/diagonal-traverse-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D integer array nums, return all elements of nums in diagonal order as shown in the below images.
//
// Example:
// Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,4,2,7,5,3,8,6,9]
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i].length <= 105
// 	1 <= sum(nums[i].length) <= 105
// 	1 <= nums[i][j] <= 105
//

/**
 * @param {number[][]} nums
 * @return {number[]}
 */
var findDiagonalOrder = function(nums) {
    const diagonals = new Map();
    let maxDiagonal = 0;
    for (let r = 0; r < nums.length; r++) {
        for (let c = 0; c < nums[r].length; c++) {
            const diagonalIndex = r + c;
            if (!diagonals.has(diagonalIndex)) {
                diagonals.set(diagonalIndex, []);
            }
            diagonals.get(diagonalIndex).push(nums[r][c]);
            maxDiagonal = Math.max(maxDiagonal, diagonalIndex);
        }
    }
    const result = [];
    for (let d = 0; d <= maxDiagonal; d++) {
        if (diagonals.has(d)) {
            const diagonalElements = diagonals.get(d);
            for (let i = diagonalElements.length - 1; i >= 0; i--) {
                result.push(diagonalElements[i]);
            }
        }
    }
    return result;
        
};
