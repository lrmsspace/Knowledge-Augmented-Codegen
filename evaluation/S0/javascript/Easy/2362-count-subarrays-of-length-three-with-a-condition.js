// Source: https://leetcode.com/problems/count-subarrays-of-length-three-with-a-condition/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, return the number of subarrays of length 3 such that the sum of the first and third numbers equals exactly half of the second number.
//
// Example:
// Input: nums = [1,2,1,4,1]
//
// Output: 1
//
// Explanation:
//
// Only the subarray [1,4,1] contains exactly 3 elements where the sum of the first and third numbers equals half the middle number.
//
// Constraints:
// 3 <= nums.length <= 100
// 	-100 <= nums[i] <= 100
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var countSubarrays = function(nums) {
    let count = 0;
    for (let i = 0; i <= nums.length - 3; i++) {
        if (nums[i] + nums[i + 2] === 2 * nums[i + 1]) {
            count++;
        }
    }
    return count;
};
