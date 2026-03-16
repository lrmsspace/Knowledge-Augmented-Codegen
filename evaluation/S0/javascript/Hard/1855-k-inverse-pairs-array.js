// Source: https://leetcode.com/problems/k-inverse-pairs-array/   |   Difficulty: Hard
//
// Problem Description:
// For an integer array nums, an inverse pair is a pair of integers [i, j] where 0 <= i < j < nums.length and nums[i] > nums[j].
//
// Given two integers n and k, return the number of different arrays consisting of numbers from 1 to n such that there are exactly k inverse pairs. Since the answer can be huge, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, k = 0
// Output: 1
// Explanation: Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pairs.
//
// Constraints:
// 1 <= n <= 1000
// 	0 <= k <= 1000
//

/**
 * @param {number} n
 * @param {number} k
 * @return {number}
 */
var kInversePairs = function(n, k) {
    const MOD = 1e9 + 7;
    const dp = Array.from({ length: n + 1 }, () => Array(k + 1).fill(0));
        
    for (let i = 0; i <= n; i++) {
        dp[i][0] = 1; // Base case: 1 way to have 0 inverse pairs (sorted array)
    }

    for (let i = 1; i <= n; i++) {
        for (let j = 1; j <= k; j++) {

            dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % MOD;
            if (j >= i) {
                dp[i][j] = (dp[i][j] - dp[i - 1][j - i] + MOD) % MOD;
            }
        }
    }
    return dp[n][k];
    
};
