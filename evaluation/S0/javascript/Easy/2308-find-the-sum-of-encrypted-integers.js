// Source: https://leetcode.com/problems/find-the-sum-of-encrypted-integers/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums containing positive integers. We define a function encrypt such that encrypt(x) replaces every digit in x with the largest digit in x. For example, encrypt(523) = 555 and encrypt(213) = 333.
//
// Return the sum of encrypted elements.
//
// Example:
// Input: nums = [1,2,3]
//
// Output: 6
//
// Explanation: The encrypted elements are [1,2,3]. The sum of encrypted elements is 1 + 2 + 3 == 6.
//
// Constraints:
// 1 <= nums.length <= 50
// 	1 <= nums[i] <= 1000
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var sumOfEncryptedInt = function(nums) {
    let totalSum = 0;
    for (const num of nums) {
        const maxDigit = Math.max(...num.toString().split('').map(digit => parseInt(digit)));
        totalSum += maxDigit;
    }
    return totalSum;
};
