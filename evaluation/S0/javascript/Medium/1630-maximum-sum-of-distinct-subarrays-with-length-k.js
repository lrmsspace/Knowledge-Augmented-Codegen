// Source: https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k. Find the maximum subarray sum of all the subarrays of nums that meet the following conditions:
//
//
// 	The length of the subarray is k, and
// 	All the elements of the subarray are distinct.
//
//
// Return the maximum subarray sum of all the subarrays that meet the conditions. If no subarray meets the conditions, return 0.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,5,4,2,9,9,9], k = 3
// Output: 15
// Explanation: The subarrays of nums with length 3 are:
// - [1,5,4] which meets the requirements and has a sum of 10.
// - [5,4,2] which meets the requirements and has a sum of 11.
// - [4,2,9] which meets the requirements and has a sum of 15.
// - [2,9,9] which does not meet the requirements because the element 9 is repeated.
// - [9,9,9] which does not meet the requirements because the element 9 is repeated.
// We return 15 because it is the maximum subarray sum of all the subarrays that meet the conditions
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maximumSubarraySum = function(nums, k) {
    const n = nums.length;
    let left = 0;
    let right = 0;
    let currentSum = 0;
    let maxSum = 0;
    const numCount = new Map();

    while (right < n) {
        const rightNum = nums[right];
        numCount.set(rightNum, (numCount.get(rightNum) || 0) + 1);
        currentSum += rightNum;

        while (numCount.get(rightNum) > 1) {
            const leftNum = nums[left];
            numCount.set(leftNum, numCount.get(leftNum) - 1);
            currentSum -= leftNum;
            left++;
        }

        if (right - left + 1 === k) {
            maxSum = Math.max(maxSum, currentSum);
            const leftNum = nums[left];
            numCount.set(leftNum, numCount.get(leftNum) - 1);
            currentSum -= leftNum;
            left++;
        }

        right++;
    }

    return maxSum;
};