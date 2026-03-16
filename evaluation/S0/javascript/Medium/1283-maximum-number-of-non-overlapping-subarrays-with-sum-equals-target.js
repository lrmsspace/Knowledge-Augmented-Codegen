// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums and an integer target, return the maximum number of non-empty non-overlapping subarrays such that the sum of values in each subarray is equal to target.
//
// Example:
// Input: nums = [1,1,1,1,1], target = 2
// Output: 2
// Explanation: There are 2 non-overlapping subarrays [1,1,1,1,1] with sum equals to target(2).
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
// 	0 <= target <= 106
//

/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number}
 */
var maxNonOverlapping = function(nums, target) {
    let count = 0;
    let currentSum = 0;
    const seenSums = new Set();
    seenSums.add(0);
    for (const num of nums) {
        currentSum += num;
        if (seenSums.has(currentSum - target)) {
            count++;
            seenSums.clear();
            currentSum = 0;
        } else {
            seenSums.add(currentSum);
        }
    }
    return count;
};