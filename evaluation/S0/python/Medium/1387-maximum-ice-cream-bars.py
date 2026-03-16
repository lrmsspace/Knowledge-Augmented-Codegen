# Source: https://leetcode.com/problems/maximum-ice-cream-bars/   |   Difficulty: Medium
#
# Problem Description:
# It is a sweltering summer day, and a boy wants to buy some ice cream bars.
#
# At the store, there are n ice cream bars. You are given an array costs of length n, where costs[i] is the price of the ith ice cream bar in coins. The boy initially has coins coins to spend, and he wants to buy as many ice cream bars as possible. 
#
# Note: The boy can buy the ice cream bars in any order.
#
# Return the maximum number of ice cream bars the boy can buy with coins coins.
#
# You must solve the problem by counting sort.
#
# Example:
# Input: costs = [1,3,2,4,1], coins = 7
# Output: 4
# Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a total price of 1 + 3 + 2 + 1 = 7.
#
# Constraints:
# costs.length == n
# 	1 <= n <= 105
# 	1 <= costs[i] <= 105
# 	1 <= coins <= 108
#

class Solution(object):
    def maxIceCream(self, costs, coins):
        """
        :type costs: List[int]
        :type coins: int
        :rtype: int
        """
        max_cost = max(costs)
        count = [0] * (max_cost + 1)

        for cost in costs:
            count[cost] += 1

        total_bars = 0

        for price in range(1, max_cost + 1):
            if coins <= 0:
                break

            if count[price] == 0:
                continue

            affordable_bars = min(count[price], coins // price)
            total_bars += affordable_bars
            coins -= affordable_bars * price

        return total_bars