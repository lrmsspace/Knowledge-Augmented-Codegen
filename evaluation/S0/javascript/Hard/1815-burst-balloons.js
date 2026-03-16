// Source: https://leetcode.com/problems/burst-balloons/   |   Difficulty: Hard
//
// Problem Description:
// You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums. You are asked to burst all the balloons.
//
// If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.
//
// Return the maximum coins you can collect by bursting the balloons wisely.
//
// Example:
// Input: nums = [3,1,5,8]
// Output: 167
// Explanation:
// nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
// coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
//
// Constraints:
// n == nums.length
// 	1 <= n <= 300
// 	0 <= nums[i] <= 100
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxCoins = function(nums) {
    const n = nums.length;
    const balloons = [1, ...nums.filter(num => num > 0), 1];
    const m = balloons.length;
    const dp = Array.from({ length: m }, () => new Array(m).fill(0));
    for (let length = 1; length < m - 1; length++) {
        for (let left = 1; left < m - length; left++) {
            const right = left + length - 1;
            for (let i = left; i <= right; i++) {
                dp[left][right] = Math.max(dp[left][right], dp[left][i - 1] + balloons[left - 1] * balloons[i] * balloons[right + 1] + dp[i + 1][right]);
            }
        }
    }
    return dp[1][m - 2];    
};
