// Source: https://leetcode.com/problems/partition-array-into-disjoint-intervals/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, partition it into two (contiguous) subarrays left and right so that:
//
//
// 	Every element in left is less than or equal to every element in right.
// 	left and right are non-empty.
// 	left has the smallest possible size.
//
//
// Return the length of left after such a partitioning.
//
// Test cases are generated such that partitioning exists.
//
// Example:
// Input: nums = [5,0,3,8,6]
// Output: 3
// Explanation: left = [5,0,3], right = [8,6]
//
// Constraints:
// 2 <= nums.length <= 105
// 	0 <= nums[i] <= 106
// 	There is at least one valid answer for the given input.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var partitionDisjoint = function(nums) {
    let leftMax = nums[0];
    let overallMax = nums[0];
    let partitionIdx = 0;
    for (let i = 1; i < nums.length; i++) {
        overallMax = Math.max(overallMax, nums[i]);
        if (nums[i] < leftMax) {
            leftMax = overallMax;
            partitionIdx = i;
        }
    }
    return partitionIdx + 1;
};  