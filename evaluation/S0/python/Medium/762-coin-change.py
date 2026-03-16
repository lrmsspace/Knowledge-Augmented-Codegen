# Source: https://leetcode.com/problems/coin-change/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
#
# Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
#
# You may assume that you have an infinite number of each kind of coin.
#
# Example:
# Input: coins = [1,2,5], amount = 11
# Output: 3
# Explanation: 11 = 5 + 5 + 1
#
# Constraints:
# 1 <= coins.length <= 12
# 	1 <= coins[i] <= 231 - 1
# 	0 <= amount <= 104
#

class Solution(object):
    def coinChange(self, coins, amount):
        """
        :type coins: List[int]
        :type amount: int
        :rtype: int
        """
        # Initialize a list to store the minimum number of coins for each amount
        dp = [float('inf')] * (amount + 1)
        dp[0] = 0  # Base case: 0 coins are needed to make amount 0

        # Iterate through each coin
        for coin in coins:
            # Update the dp array for all amounts that can be reached with the current coin
            for x in range(coin, amount + 1):
                dp[x] = min(dp[x], dp[x - coin] + 1)

        # If dp[amount] is still infinity, it means it's not possible to make that amount
        return dp[amount] if dp[amount] != float('inf') else -1