# Source: https://leetcode.com/problems/inverse-coin-change/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 1-indexed integer array numWays, where numWays[i] represents the number of ways to select a total amount i using an infinite supply of some fixed coin denominations. Each denomination is a positive integer with value at most numWays.length.
#
# However, the exact coin denominations have been lost. Your task is to recover the set of denominations that could have resulted in the given numWays array.
#
# Return a sorted array containing unique integers which represents this set of denominations.
#
# If no such set exists, return an empty array.
#
# Example:
# Input: numWays = [0,1,0,2,0,3,0,4,0,5]
#
# Output: [2,4,6]
#
# Explanation:
#
#
# 	
# 		
# 			Amount
# 			Number of ways
# 			Explanation
# 		
# 		
# 			1
# 			0
# 			There is no way to select coins with total value 1.
# 		
# 		
# 			2
# 			1
# 			The only way is [2].
# 		
# 		
# 			3
# 			0
# 			There is no way to select coins with total value 3.
# 		
# 		
# 			4
# 			2
# 			The ways are [2, 2] and [4].
# 		
# 		
# 			5
# 			0
# 			There is no way to select coins with total value 5.
# 		
# 		
# 			6
# 			3
# 			The ways are [2, 2, 2], [2, 4], and [6].
# 		
# 		
# 			7
# 			0
# 			There is no way to select coins with total value 7.
# 		
# 		
# 			8
# 			4
# 			The ways are [2, 2, 2, 2], [2, 2, 4], [2, 6], and [4, 4].
# 		
# 		
# 			9
# 			0
# 			There is no way to select coins with total value 9.
# 		
# 		
# 			10
# 			5
# 			The ways are [2, 2, 2, 2, 2], [2, 2, 2, 4], [2, 4, 4], [2, 2, 6], and [4, 6].
#
# Constraints:
# 1 <= numWays.length <= 100
# 	0 <= numWays[i] <= 2 * 108
#

class Solution(object):
    def findCoins(self, numWays):
        """
        :type numWays: List[int]
        :rtype: List[int]
        """
        n = len(numWays)
        dp = [0] * n
        coins = []

        for coin in range(1, n):
            if numWays[coin] == 0:
                continue

            temp_dp = dp[:]
            for amount in range(coin, n):
                temp_dp[amount] += temp_dp[amount - coin] + (1 if amount == coin else 0)

            if temp_dp == numWays:
                coins.append(coin)
                dp = temp_dp

        return coins if dp == numWays else []