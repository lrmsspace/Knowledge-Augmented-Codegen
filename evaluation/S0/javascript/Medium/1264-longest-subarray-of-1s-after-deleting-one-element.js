// Source: https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary array nums, you should delete one element from it.
//
// Return the size of the longest non-empty subarray containing only 1's in the resulting array. Return 0 if there is no such subarray.
//
// Example:
// Input: nums = [1,1,0,1]
// Output: 3
// Explanation: After deleting the number in position 2, [1,1,1] contains 3 numbers with value of 1's.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is either 0 or 1.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var longestSubarray = function(nums) {
    let left = 0;
    let right = 0;
    let zeroCount = 0;
    let maxLength = 0;
    const n = nums.length;
    while (right < n) {
        if (nums[right] === 0) {
            zeroCount++;
        }
        while (zeroCount > 1) {
            if (nums[left] === 0) {
                zeroCount--;
            }
            left++;
        }
        maxLength = Math.max(maxLength, right - left);
        right++;
    }
    return maxLength;
};