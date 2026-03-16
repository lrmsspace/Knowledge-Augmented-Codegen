# Source: https://leetcode.com/problems/number-of-ways-to-reach-a-position-after-exactly-k-steps/   |   Difficulty: Medium
#
# Problem Description:
# You are given two positive integers startPos and endPos. Initially, you are standing at position startPos on an infinite number line. With one step, you can move either one position to the left, or one position to the right.
#
# Given a positive integer k, return the number of different ways to reach the position endPos starting from startPos, such that you perform exactly k steps. Since the answer may be very large, return it modulo 109 + 7.
#
# Two ways are considered different if the order of the steps made is not exactly the same.
#
# Note that the number line includes negative integers.
#
# Example:
# Input: startPos = 1, endPos = 2, k = 3
# Output: 3
# Explanation: We can reach position 2 from 1 in exactly 3 steps in three ways:
# - 1 -> 2 -> 3 -> 2.
# - 1 -> 2 -> 1 -> 2.
# - 1 -> 0 -> 1 -> 2.
# It can be proven that no other way is possible, so we return 3.
#
# Constraints:
# 1 <= startPos, endPos, k <= 1000
#

class Solution(object):
    def numberOfWays(self, startPos, endPos, k):
        """
        :type startPos: int
        :type endPos: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        distance = abs(endPos - startPos)
        
        # If the distance is greater than k or if the parity of distance and k doesn't match, return 0
        if distance > k or (k - distance) % 2 != 0:
            return 0
        
        # Calculate the number of steps to the right
        right_steps = (k + distance) // 2
        
        # Calculate nCr using dynamic programming
        dp = [0] * (right_steps + 1)
        dp[0] = 1
        
        for i in range(1, k + 1):
            for j in range(min(i, right_steps), 0, -1):
                dp[j] = (dp[j] + dp[j - 1]) % MOD
        
        return dp[right_steps]