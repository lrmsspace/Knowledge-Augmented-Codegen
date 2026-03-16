// Source: https://leetcode.com/problems/find-the-duplicate-number/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.
//
// There is only one repeated number in nums, return this repeated number.
//
// You must solve the problem without modifying the array nums and using only constant extra space.
//
// Example:
// Input: nums = [1,3,4,2,2]
// Output: 2
//
// Constraints:
// 1 <= n <= 105
// 	nums.length == n + 1
// 	1 <= nums[i] <= n
// 	All the integers in nums appear only once except for precisely one integer which appears two or more times.
//
//
//  
// Follow up:
//
//
// 	How can we prove that at least one duplicate number must exist in nums?
// 	Can you solve the problem in linear runtime complexity?
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var findDuplicate = function(nums) {
    let slow = nums[0];
    let fast = nums[0];
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow !== fast);

    slow = nums[0];
    while (slow !== fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
};