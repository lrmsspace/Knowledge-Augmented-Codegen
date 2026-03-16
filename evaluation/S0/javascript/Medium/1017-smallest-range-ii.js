// Source: https://leetcode.com/problems/smallest-range-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// For each index i where 0 <= i < nums.length, change nums[i] to be either nums[i] + k or nums[i] - k.
//
// The score of nums is the difference between the maximum and minimum elements in nums.
//
// Return the minimum score of nums after changing the values at each index.
//
// Example:
// Input: nums = [1], k = 0
// Output: 0
// Explanation: The score is max(nums) - min(nums) = 1 - 1 = 0.
//
// Constraints:
// 1 <= nums.length <= 104
// 	0 <= nums[i] <= 104
// 	0 <= k <= 104
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var smallestRangeII = function(nums, k) {
    nums.sort((a, b) => a - b);
    let n = nums.length;
    let result = nums[n - 1] - nums[0];
    for (let i = 0; i < n - 1; i++) {
        let high = Math.max(nums[n - 1] - k, nums[i] + k);
        let low = Math.min(nums[0] + k, nums[i + 1] - k);
        result = Math.min(result, high - low);
    }
    return result;
};