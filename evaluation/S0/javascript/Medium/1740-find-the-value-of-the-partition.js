// Source: https://leetcode.com/problems/find-the-value-of-the-partition/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer array nums.
//
// Partition nums into two arrays, nums1 and nums2, such that:
//
//
// 	Each element of the array nums belongs to either the array nums1 or the array nums2.
// 	Both arrays are non-empty.
// 	The value of the partition is minimized.
//
//
// The value of the partition is |max(nums1) - min(nums2)|.
//
// Here, max(nums1) denotes the maximum element of the array nums1, and min(nums2) denotes the minimum element of the array nums2.
//
// Return the integer denoting the value of such partition.
//
// Example:
// Input: nums = [1,3,2,4]
// Output: 1
// Explanation: We can partition the array nums into nums1 = [1,2] and nums2 = [3,4].
// - The maximum element of the array nums1 is equal to 2.
// - The minimum element of the array nums2 is equal to 3.
// The value of the partition is |2 - 3| = 1. 
// It can be proven that 1 is the minimum value out of all partitions.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var findValueOfPartition = function(nums) {
    nums.sort((a, b) => a - b);
    let minDiff = Infinity;
    for (let i = 1; i < nums.length; i++) {
        minDiff = Math.min(minDiff, nums[i] - nums[i - 1]);
    }
    return minDiff;
};
