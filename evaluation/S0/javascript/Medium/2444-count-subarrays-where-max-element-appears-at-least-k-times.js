// Source: https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a positive integer k.
//
// Return the number of subarrays where the maximum element of nums appears at least k times in that subarray.
//
// A subarray is a contiguous sequence of elements within an array.
//
// Example:
// Input: nums = [1,3,2,3,3], k = 2
// Output: 6
// Explanation: The subarrays that contain the element 3 at least 2 times are: [1,3,2,3], [1,3,2,3,3], [3,2,3], [3,2,3,3], [2,3,3] and [3,3].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	1 <= k <= 105
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var countSubarrays = function(nums, k) {
    const n = nums.length;
    let totalSubarrays = 0;
    let left = 0;
    let right = 0;
    const freqMap = new Map();
    while (right < n) {
        freqMap.set(nums[right], (freqMap.get(nums[right]) || 0) + 1);
        while (freqMap.get(nums[right]) > k) {
            freqMap.set(nums[left], freqMap.get(nums[left]) - 1);
            left++;
        }
        totalSubarrays += right - left + 1;
        right++;
    }
    return totalSubarrays;
};