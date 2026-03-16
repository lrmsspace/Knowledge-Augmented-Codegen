// Source: https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers called nums, you can perform any of the following operation while nums contains at least 2 elements:
//
//
// 	Choose the first two elements of nums and delete them.
// 	Choose the last two elements of nums and delete them.
// 	Choose the first and the last elements of nums and delete them.
//
//
// The score of the operation is the sum of the deleted elements.
//
// Your task is to find the maximum number of operations that can be performed, such that all operations have the same score.
//
// Return the maximum number of operations possible that satisfy the condition mentioned above.
//
// Example:
// Input: nums = [3,2,1,2,3,4]
// Output: 3
// Explanation: We perform the following operations:
// - Delete the first two elements, with score 3 + 2 = 5, nums = [1,2,3,4].
// - Delete the first and the last elements, with score 1 + 4 = 5, nums = [2,3].
// - Delete the first and the last elements, with score 2 + 3 = 5, nums = [].
// We are unable to perform any more operations as nums is empty.
//
// Constraints:
// 2 <= nums.length <= 2000
// 	1 <= nums[i] <= 1000
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxOperations = function(nums) {
    const n = nums.length;      
    const scoreCount = new Map();
    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            const score = nums[i] + nums[j];
            scoreCount.set(score, (scoreCount.get(score) || 0) + 1);
        }
    } 
    let maxOperations = 0;
    for (const count of scoreCount.values()) {
        maxOperations = Math.max(maxOperations, Math.floor(count / 2));
    }
    return maxOperations;
};
