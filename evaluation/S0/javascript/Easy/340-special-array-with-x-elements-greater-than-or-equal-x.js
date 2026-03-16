// Source: https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array nums of non-negative integers. nums is considered special if there exists a number x such that there are exactly x numbers in nums that are greater than or equal to x.
//
// Notice that x does not have to be an element in nums.
//
// Return x if the array is special, otherwise, return -1. It can be proven that if nums is special, the value for x is unique.
//
// Example:
// Input: nums = [3,5]
// Output: 2
// Explanation: There are 2 values (3 and 5) that are greater than or equal to 2.
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 1000
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var specialArray = function(nums) {
    const n = nums.length;
    for (let x = 1; x <= n; x++) {
        let count = 0;  
        for (const num of nums) {
            if (num >= x) {
                count++;
            }
        }
        if (count === x) {
            return x;
        }
    }
    return -1;  
};
