// Source: https://leetcode.com/problems/contains-duplicate-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums and an integer k, return true if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.
//
// Example:
// Input: nums = [1,2,3,1], k = 3
// Output: true
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	0 <= k <= 105
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {boolean}
 */
var containsNearbyDuplicate = function(nums, k) {
    const numMap = new Map();
    for (let i = 0; i < nums.length; i++) {
        const num = nums[i];
        if (numMap.has(num)) {
            const prevIndex = numMap.get(num);
            if (i - prevIndex <= k) {
                return true;
            }
        }
        numMap.set(num, i);
    }
    return false;
};
