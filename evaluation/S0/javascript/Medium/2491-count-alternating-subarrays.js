// Source: https://leetcode.com/problems/count-alternating-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary array nums.
//
// We call a subarray alternating if no two adjacent elements in the subarray have the same value.
//
// Return the number of alternating subarrays in nums.
//
// Example:
// Input: nums = [0,1,1,1]
//
// Output: 5
//
// Explanation:
//
// The following subarrays are alternating: [0], [1], [1], [1], and [0,1].
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is either 0 or 1.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var countAlternatingSubarrays = function(nums) {
    let count = 0;
    let length = 1;
    for (let i = 1; i < nums.length; i++) {
        if (nums[i] !== nums[i - 1]) {
            length++;
        } else {
            length = 1;
        }
        count += length;
    }
    return count;
};