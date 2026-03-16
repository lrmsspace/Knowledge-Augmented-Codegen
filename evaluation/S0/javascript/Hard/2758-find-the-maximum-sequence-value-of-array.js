// Source: https://leetcode.com/problems/find-the-maximum-sequence-value-of-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k.
//
// The value of a sequence seq of size 2 * x is defined as:
//
//
// 	(seq[0] OR seq[1] OR ... OR seq[x - 1]) XOR (seq[x] OR seq[x + 1] OR ... OR seq[2 * x - 1]).
//
//
// Return the maximum value of any subsequence of nums having size 2 * k.
//
// Example:
// Input: nums = [2,6,7], k = 1
//
// Output: 5
//
// Explanation:
//
// The subsequence [2, 7] has the maximum value of 2 XOR 7 = 5.
//
// Constraints:
// 2 <= nums.length <= 400
// 	1 <= nums[i] < 27
// 	1 <= k <= nums.length / 2
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maxValue = function(nums, k) {
    const n = nums.length;
    const dp = Array.from({ length: n + 1 }, () => Array(k + 1).fill(0));
    for (let i = 1; i <= n; i++) {
        for (let j = 0; j <= Math.min(k, Math.floor(i / 2)); j++) {
            dp[i][j] = dp[i - 1][j];
            if (j > 0) {
                let orFirst = 0;
                let orSecond = 0;
                for (let x = i - 1; x >= 0; x--) {
                    orFirst |= nums[x];
                    if (i - x - 1 > 0) {
                        orSecond |= nums[i - (i - x - 1)];
                    }
                    dp[i][j] = Math.max(dp[i][j], dp[x][j - 1] ^ (orFirst | orSecond));
                }
            }
        }
    }
    return dp[n][k];
};
