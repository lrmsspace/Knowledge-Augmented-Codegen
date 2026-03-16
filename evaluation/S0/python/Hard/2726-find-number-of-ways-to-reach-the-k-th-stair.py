# Source: https://leetcode.com/problems/find-number-of-ways-to-reach-the-k-th-stair/   |   Difficulty: Hard
#
# Problem Description:
# You are given a non-negative integer k. There exists a staircase with an infinite number of stairs, with the lowest stair numbered 0.
#
# Alice has an integer jump, with an initial value of 0. She starts on stair 1 and wants to reach stair k using any number of operations. If she is on stair i, in one operation she can:
#
#
# 	Go down to stair i - 1. This operation cannot be used consecutively or on stair 0.
# 	Go up to stair i + 2jump. And then, jump becomes jump + 1.
#
#
# Return the total number of ways Alice can reach stair k.
#
# Note that it is possible that Alice reaches the stair k, and performs some operations to reach the stair k again.
#
# Example:
# Input: k = 0
#
# Output: 2
#
# Explanation:
#
# The 2 possible ways of reaching stair 0 are:
#
#
# 	Alice starts at stair 1.
# 	
# 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
# 	
# 	
# 	Alice starts at stair 1.
# 	
# 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
# 		Using an operation of the second type, she goes up 20 stairs to reach stair 1.
# 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
#
# Constraints:
# 0 <= k <= 109
#

class Solution(object):
    def waysToReachStair(self, k):
        """
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        # dp[jump][stair] = number of ways to reach stair with jump
        dp = [[0] * (k + 3) for _ in range(k + 3)]
        dp[0][1] = 1  # Start at stair 1 with jump 0
        
        for jump in range(k + 1):
            for stair in range(k + 2):
                if stair > 0:
                    dp[jump][stair - 1] = (dp[jump][stair - 1] + dp[jump][stair]) % MOD
                dp[jump + 1][stair + 2] = (dp[jump + 1][stair + 2] + dp[jump][stair]) % MOD
        
        return sum(dp[jump][k] for jump in range(k + 2)) % MOD