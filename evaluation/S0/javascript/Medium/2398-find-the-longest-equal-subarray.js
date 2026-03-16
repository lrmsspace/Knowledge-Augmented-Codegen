// Source: https://leetcode.com/problems/find-the-longest-equal-subarray/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer k.
//
// A subarray is called equal if all of its elements are equal. Note that the empty subarray is an equal subarray.
//
// Return the length of the longest possible equal subarray after deleting at most k elements from nums.
//
// A subarray is a contiguous, possibly empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,3,2,3,1,3], k = 3
// Output: 3
// Explanation: It's optimal to delete the elements at index 2 and index 4.
// After deleting them, nums becomes equal to [1, 3, 3, 3].
// The longest equal subarray starts at i = 1 and ends at j = 3 with length equal to 3.
// It can be proven that no longer equal subarrays can be created.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= nums.length
// 	0 <= k <= nums.length
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var longestEqualSubarray = function(nums, k) {
    const n = nums.length;
    const indexMap = new Map();
    for (let i = 0; i < n; i++) {
        if (!indexMap.has(nums[i])) {
            indexMap.set(nums[i], []);
        }
        indexMap.get(nums[i]).push(i);
    }
    let maxLength = 0;
    for (const indices of indexMap.values()) {
        let left = 0;
        for (let right = 0; right < indices.length; right++) {
            while (indices[right] - indices[left] - (right - left) > k) {
                left++;
            }
            maxLength = Math.max(maxLength, right - left + 1);
        }
    }
    return maxLength;   
};
