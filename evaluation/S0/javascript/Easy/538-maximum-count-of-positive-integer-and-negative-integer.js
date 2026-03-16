// Source: https://leetcode.com/problems/maximum-count-of-positive-integer-and-negative-integer/   |   Difficulty: Easy
//
// Problem Description:
// Given an array nums sorted in non-decreasing order, return the maximum between the number of positive integers and the number of negative integers.
//
//
// 	In other words, if the number of positive integers in nums is pos and the number of negative integers is neg, then return the maximum of pos and neg.
//
//
// Note that 0 is neither positive nor negative.
//
// Example:
// Input: nums = [-2,-1,-1,1,2,3]
// Output: 3
// Explanation: There are 3 positive integers and 3 negative integers. The maximum count among them is 3.
//
// Constraints:
// 1 <= nums.length <= 2000
// 	-2000 <= nums[i] <= 2000
// 	nums is sorted in a non-decreasing order.
//
//
//  
// Follow up: Can you solve the problem in O(log(n)) time complexity?
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maximumCount = function(nums) {
    let posCount = 0;
    let negCount = 0;
    for (const num of nums) {
        if (num > 0) {
            posCount++;
        } else if (num < 0) {
            negCount++;
        }
    }
    return Math.max(posCount, negCount);
};