# Source: https://leetcode.com/problems/dice-roll-simulation/   |   Difficulty: Hard
#
# Problem Description:
# A die simulator generates a random number from 1 to 6 for each roll. You introduced a constraint to the generator such that it cannot roll the number i more than rollMax[i] (1-indexed) consecutive times.
#
# Given an array of integers rollMax and an integer n, return the number of distinct sequences that can be obtained with exact n rolls. Since the answer may be too large, return it modulo 109 + 7.
#
# Two sequences are considered different if at least one element differs from each other.
#
# Example:
# Input: n = 2, rollMax = [1,1,2,2,2,3]
# Output: 34
# Explanation: There will be 2 rolls of die, if there are no constraints on the die, there are 6 * 6 = 36 possible combinations. In this case, looking at rollMax array, the numbers 1 and 2 appear at most once consecutively, therefore sequences (1,1) and (2,2) cannot occur, so the final answer is 36-2 = 34.
#
# Constraints:
# 1 <= n <= 5000
# 	rollMax.length == 6
# 	1 <= rollMax[i] <= 15
#

class Solution(object):
    def dieSimulator(self, n, rollMax):
        """
        :type n: int
        :type rollMax: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        dp = [[0] * 6 for _ in range(n)]
        
        for j in range(6):
            dp[0][j] = 1
        
        for i in range(1, n):
            for j in range(6):
                for k in range(6):
                    if j != k:
                        dp[i][j] = (dp[i][j] + dp[i-1][k]) % MOD
                    else:
                        for l in range(1, rollMax[j]):
                            if i - l >= 0:
                                dp[i][j] = (dp[i][j] + dp[i-l-1][k]) % MOD
        
        return sum(dp[n-1]) % MOD