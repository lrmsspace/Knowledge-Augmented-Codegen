// Source: https://leetcode.com/problems/shortest-unsorted-continuous-subarray/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, you need to find one continuous subarray such that if you only sort this subarray in non-decreasing order, then the whole array will be sorted in non-decreasing order.
//
// Return the shortest such subarray and output its length.
//
// Example:
// Input: nums = [2,6,4,8,10,9,15]
// Output: 5
// Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
//
// Constraints:
// 1 <= nums.length <= 104
// 	-105 <= nums[i] <= 105
//
//
//  
// Follow up: Can you solve it in O(n) time complexity?
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var findUnsortedSubarray = function(nums) {
    const sortedNums = [...nums].sort((a, b) => a - b);
    let start = nums.length, end = 0;
    for (let i = 0; i < nums.length; i++) {
        if (nums[i] !== sortedNums[i]) {
            start = Math.min(start, i);
            end = Math.max(end, i);
        }
    }
    return end >= start ? end - start + 1 : 0;
};