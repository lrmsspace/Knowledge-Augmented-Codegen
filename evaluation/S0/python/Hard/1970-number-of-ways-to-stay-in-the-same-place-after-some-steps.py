# Source: https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/   |   Difficulty: Hard
#
# Problem Description:
# You have a pointer at index 0 in an array of size arrLen. At each step, you can move 1 position to the left, 1 position to the right in the array, or stay in the same place (The pointer should not be placed outside the array at any time).
#
# Given two integers steps and arrLen, return the number of ways such that your pointer is still at index 0 after exactly steps steps. Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: steps = 3, arrLen = 2
# Output: 4
# Explanation: There are 4 differents ways to stay at index 0 after 3 steps.
# Right, Left, Stay
# Stay, Right, Left
# Right, Stay, Left
# Stay, Stay, Stay
#
# Constraints:
# 1 <= steps <= 500
# 	1 <= arrLen <= 106
#

class Solution(object):
    def numWays(self, steps, arrLen):
        """
        :type steps: int
        :type arrLen: int
        :rtype: int
        """
        MOD = 10**9 + 7
        max_pos = min(steps // 2 + 1, arrLen)
        dp = [0] * max_pos
        dp[0] = 1
        
        for _ in range(steps):
            new_dp = [0] * max_pos
            for i in range(max_pos):
                new_dp[i] = dp[i] % MOD
                if i - 1 >= 0:
                    new_dp[i] = (new_dp[i] + dp[i - 1]) % MOD
                if i + 1 < max_pos:
                    new_dp[i] = (new_dp[i] + dp[i + 1]) % MOD
            dp = new_dp
        
        return dp[0] % MOD