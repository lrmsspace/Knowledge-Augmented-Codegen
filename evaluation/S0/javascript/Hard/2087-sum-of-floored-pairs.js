// Source: https://leetcode.com/problems/sum-of-floored-pairs/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the sum of floor(nums[i] / nums[j]) for all pairs of indices 0 <= i, j < nums.length in the array. Since the answer may be too large, return it modulo 109 + 7.
//
// The floor() function returns the integer part of the division.
//
// Example:
// Input: nums = [2,5,9]
// Output: 10
// Explanation:
// floor(2 / 5) = floor(2 / 9) = floor(5 / 9) = 0
// floor(2 / 2) = floor(5 / 5) = floor(9 / 9) = 1
// floor(5 / 2) = 2
// floor(9 / 2) = 4
// floor(9 / 5) = 1
// We calculate the floor of the division for every pair of indices in the array then sum them up.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var sumOfFlooredPairs = function(nums) {
    const MOD = 1e9 + 7;
    const maxNum = Math.max(...nums);
    const count = new Array(maxNum + 1).fill(0);
    for (const num of nums) {
        count[num]++;
    }
    const prefixCount = new Array(maxNum + 1).fill(0);
    for (let i = 1; i <= maxNum; i++) {
        prefixCount[i] = prefixCount[i - 1] + count[i];
    }
    let result = 0;
    for (let i = 1; i <= maxNum; i++) {
        if (count[i] > 0) {
            for (let j = i; j <= maxNum; j += i) {
                const pairs = count[i] * (prefixCount[j] - prefixCount[j - i]);
                result = (result + pairs * Math.floor(j / i)) % MOD;
            }
        }
    }
    return result;  
};
