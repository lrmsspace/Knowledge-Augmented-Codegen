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

class Solution {
    public int numRollsToTarget(int n, int k, int target) {
        int MOD = 1_000_000_007;
        int[][] dp = new int[n + 1][target + 1];
        dp[0][0] = 1;

        for (int dice = 1; dice <= n; dice++) {
            for (int t = 1; t <= target; t++) {
                for (int face = 1; face <= k; face++) {
                    if (t - face >= 0) {
                        dp[dice][t] = (dp[dice][t] + dp[dice - 1][t - face]) % MOD;
                    }
                }
            }
        }

        return dp[n][target];           
    }
}
