// Source: https://leetcode.com/problems/split-array-largest-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.
//
// Return the minimized largest sum of the split.
//
// A subarray is a contiguous part of the array.
//
// Example:
// Input: nums = [7,2,5,10,8], k = 2
// Output: 18
// Explanation: There are four ways to split nums into two subarrays.
// The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	0 <= nums[i] <= 106
// 	1 <= k <= min(50, nums.length)
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var splitArray = function(nums, k) {
    const n = nums.length;
    let left = Math.max(...nums), right = nums.reduce((a, b) => a + b, 0);
    while (left < right) {
        const mid = Math.floor((left + right) / 2);
        let currentSum = 0, splits = 1;
        for (let num of nums) {
            if (currentSum + num > mid) {
                splits++;
                currentSum = num;
            } else {
                currentSum += num;
            }
        }
        if (splits > k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;    
    
};
