// Source: https://leetcode.com/problems/check-if-it-is-a-good-array/   |   Difficulty: Hard
//
// Problem Description:
// Given an array nums of positive integers. Your task is to select some subset of nums, multiply each element by an integer and add all these numbers. The array is said to be good if you can obtain a sum of 1 from the array by any possible subset and multiplicand.
//
// Return True if the array is good otherwise return False.
//
// Example:
// Input: nums = [12,5,7,23]
// Output: true
// Explanation: Pick numbers 5 and 7.
// 5*3 + 7*(-2) = 1
//
// Constraints:
// 1 <= nums.length <= 10^5
// 	1 <= nums[i] <= 10^9
//

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var isGoodArray = function(nums) {
    const gcd = (a, b) => {
        while (b) {
            [a, b] = [b, a % b];
        }
        return a;
    };

    let currentGCD = nums[0];
    for (let i = 1; i < nums.length; i++) {
        currentGCD = gcd(currentGCD, nums[i]);
        if (currentGCD === 1) {
            return true;
        }
    }
    return currentGCD === 1;
};
