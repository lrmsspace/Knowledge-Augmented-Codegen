// Source: https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/   |   Difficulty: Easy
//
// Problem Description:
// Given an binary array nums and an integer k, return true if all 1's are at least k places away from each other, otherwise return false.
//
// Example:
// Input: nums = [1,0,0,0,1,0,0,1], k = 2
// Output: true
// Explanation: Each of the 1s are at least 2 places away from each other.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= k <= nums.length
// 	nums[i] is 0 or 1
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {boolean}
 */
var kLengthApart = function(nums, k) {
    let lastOneIndex = -1;
    for (let i = 0; i < nums.length; i++) {
        if (nums[i] === 1) {
            if (lastOneIndex !== -1 && i - lastOneIndex - 1 < k) {
                return false;
            }
            lastOneIndex = i;
        }
    }
    return true;
};
