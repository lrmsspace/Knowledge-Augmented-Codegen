// Source: https://leetcode.com/problems/contains-duplicate/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
//
// Example:
// Input: nums = [1,2,3,1]
//
// Output: true
//
// Explanation:
//
// The element 1 occurs at the indices 0 and 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var containsDuplicate = function(nums) {
    const numSet = new Set();
    for (const num of nums) {
        if (numSet.has(num)) {
            return true;
        }
        numSet.add(num);
    }
    return false;
};
