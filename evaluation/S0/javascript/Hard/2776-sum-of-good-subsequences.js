// Source: https://leetcode.com/problems/sum-of-good-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. A good subsequence is defined as a subsequence of nums where the absolute difference between any two consecutive elements in the subsequence is exactly 1.
//
// Return the sum of all possible good subsequences of nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Note that a subsequence of size 1 is considered good by definition.
//
// Example:
// Input: nums = [1,2,1]
//
// Output: 14
//
// Explanation:
//
//
// 	Good subsequences are: [1], [2], [1], [1,2], [2,1], [1,2,1].
// 	The sum of elements in these subsequences is 14.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var sumOfGoodSubsequences = function(nums) {
    const MOD = 1e9 + 7;
    const maxNum = Math.max(...nums);
    const freq = new Array(maxNum + 1).fill(0);
    for (const num of nums) {
        freq[num]++;
    }
    const dp = new Array(maxNum + 1).fill(0);
    let result = 0;
    for (let i = 0; i <= maxNum; i++) {
        if (freq[i] > 0) {
            dp[i] = (dp[i] + freq[i]) % MOD;
            if (i > 0) {
                dp[i] = (dp[i] + dp[i - 1] * freq[i]) % MOD;
            }
            if (i < maxNum) {
                dp[i] = (dp[i] + dp[i + 1] * freq[i]) % MOD;
            }
            result = (result + dp[i]) % MOD;
        }
    }
    return result;
};
