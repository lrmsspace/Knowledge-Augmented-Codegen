// Source: https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/   |   Difficulty: Medium
//
// Problem Description:
// You have n dice, and each dice has k faces numbered from 1 to k.
//
// Given three integers n, k, and target, return the number of possible ways (out of the kn total ways) to roll the dice, so the sum of the face-up numbers equals target. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: n = 1, k = 6, target = 3
// Output: 1
// Explanation: You throw one die with 6 faces.
// There is only one way to get a sum of 3.
//
// Constraints:
// 1 <= n, k <= 30
// 	1 <= target <= 1000
//

/**
 * @param {number} n
 * @param {number} k
 * @param {number} target
 * @return {number}
 */
var numRollsToTarget = function(n, k, target) {
    const MOD = 1e9 + 7;
    const dp = Array.from({ length: n + 1 }, () => Array(target + 1).fill(0));
    dp[0][0] = 1;
    for (let dice = 1; dice <= n; dice++) {
        for (let t = 1; t <= target; t++) {
            for (let face = 1; face <= k; face++) {
                if (t - face >= 0) {
                    dp[dice][t] = (dp[dice][t] + dp[dice - 1][t - face]) % MOD;
                }
            }
        }
    }
    return dp[n][target];
        
};
