// Source: https://leetcode.com/problems/wiggle-sort-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
//
// You may assume the input array always has a valid answer.
//
// Example:
// Input: nums = [1,5,1,1,6,4]
// Output: [1,6,1,5,1,4]
// Explanation: [1,4,1,5,1,6] is also accepted.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	0 <= nums[i] <= 5000
// 	It is guaranteed that there will be an answer for the given input nums.
//
//
//  
// Follow Up: Can you do it in O(n) time and/or in-place with O(1) extra space?
//

/**
 * @param {number[]} nums
 * @return {void} Do not return anything, modify nums in-place instead.
 */
var wiggleSort = function(nums) {
    const sorted = [...nums].sort((a, b) => a - b);
    const n = nums.length;
    let left = Math.floor((n - 1) / 2);
    let right = n - 1;
    for (let i = 0; i < n; i++) {
        nums[i] = (i % 2 === 0) ? sorted[left--] : sorted[right--];
    }
        
};
