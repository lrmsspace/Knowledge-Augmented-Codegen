// Source: https://leetcode.com/problems/binary-subarrays-with-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary array nums and an integer goal, return the number of non-empty subarrays with a sum goal.
//
// A subarray is a contiguous part of the array.
//
// Example:
// Input: nums = [1,0,1,0,1], goal = 2
// Output: 4
// Explanation: The 4 subarrays are bolded and underlined below:
// [1,0,1,0,1]
// [1,0,1,0,1]
// [1,0,1,0,1]
// [1,0,1,0,1]
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	nums[i] is either 0 or 1.
// 	0 <= goal <= nums.length
//

/**
 * @param {number[]} nums
 * @param {number} goal
 * @return {number}
 */
var numSubarraysWithSum = function(nums, goal) {
    const prefixSumCount = new Map();
    prefixSumCount.set(0, 1); // Base case: one way to have a prefix sum of 0 
    let currentSum = 0;
    let result = 0;
    for (const num of nums) {
        currentSum += num;
        const complement = currentSum - goal;
        if (prefixSumCount.has(complement)) {
            result += prefixSumCount.get(complement);
        }
        prefixSumCount.set(currentSum, (prefixSumCount.get(currentSum) || 0) + 1);
    }
    return result;      
};
