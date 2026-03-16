// Source: https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// The frequency of an element x is the number of times it occurs in an array.
//
// An array is called good if the frequency of each element in this array is less than or equal to k.
//
// Return the length of the longest good subarray of nums.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,3,1,2,3,1,2], k = 2
// Output: 6
// Explanation: The longest possible good subarray is [1,2,3,1,2,3] since the values 1, 2, and 3 occur at most twice in this subarray. Note that the subarrays [2,3,1,2,3,1] and [3,1,2,3,1,2] are also good.
// It can be shown that there are no good subarrays with length more than 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= nums.length
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maxSubarrayLength = function(nums, k) {
    const n = nums.length;
    let left = 0;
    let right = 0;
    const freqMap = new Map();
    let maxLength = 0;
    while (right < n) {
        freqMap.set(nums[right], (freqMap.get(nums[right]) || 0) + 1);
        while (freqMap.get(nums[right]) > k) {
            freqMap.set(nums[left], freqMap.get(nums[left]) - 1);
            left++;
        }
        maxLength = Math.max(maxLength, right - left + 1);
        right++;
    }
    return maxLength;
};