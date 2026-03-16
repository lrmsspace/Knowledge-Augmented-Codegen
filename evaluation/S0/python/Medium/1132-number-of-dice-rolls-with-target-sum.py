# Source: https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/   |   Difficulty: Medium
#
# Problem Description:
# You have n dice, and each dice has k faces numbered from 1 to k.
#
# Given three integers n, k, and target, return the number of possible ways (out of the kn total ways) to roll the dice, so the sum of the face-up numbers equals target. Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: n = 1, k = 6, target = 3
# Output: 1
# Explanation: You throw one die with 6 faces.
# There is only one way to get a sum of 3.
#
# Constraints:
# 1 <= n, k <= 30
# 	1 <= target <= 1000
#

class Solution(object):
    def numRollsToTarget(self, n, k, target):
        """
        :type n: int
        :type k: int
        :type target: int
        :rtype: int
        """
        MOD = 10**9 + 7
        dp = [[0] * (target + 1) for _ in range(n + 1)]
        dp[0][0] = 1

        for dice in range(1, n + 1):
            for t in range(1, target + 1):
                for face in range(1, k + 1):
                    if t - face >= 0:
                        dp[dice][t] = (dp[dice][t] + dp[dice - 1][t - face]) % MOD

        return dp[n][target]