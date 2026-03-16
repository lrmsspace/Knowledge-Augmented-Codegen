// Source: https://leetcode.com/problems/maximum-subarray/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, find the subarray with the largest sum, and return its sum.
//
// Example:
// Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
// Output: 6
// Explanation: The subarray [4,-1,2,1] has the largest sum 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
//
//
//  
// Follow up: If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxSubArray = function(nums) {
    let maxSoFar = nums[0];
    let maxEndingHere = nums[0];
    for (let i = 1; i < nums.length; i++) {
        maxEndingHere = Math.max(nums[i], maxEndingHere + nums[i]);
        maxSoFar = Math.max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
};
