# Source: https://leetcode.com/problems/maximum-energy-boost-from-two-drinks/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integer arrays energyDrinkA and energyDrinkB of the same length n by a futuristic sports scientist. These arrays represent the energy boosts per hour provided by two different energy drinks, A and B, respectively.
#
# You want to maximize your total energy boost by drinking one energy drink per hour. However, if you want to switch from consuming one energy drink to the other, you need to wait for one hour to cleanse your system (meaning you won't get any energy boost in that hour).
#
# Return the maximum total energy boost you can gain in the next n hours.
#
# Note that you can start consuming either of the two energy drinks.
#
# Example:
# Input: energyDrinkA = [1,3,1], energyDrinkB = [3,1,1]
#
# Output: 5
#
# Explanation:
#
# To gain an energy boost of 5, drink only the energy drink A (or only B).
#
# Constraints:
# n == energyDrinkA.length == energyDrinkB.length
# 	3 <= n <= 105
# 	1 <= energyDrinkA[i], energyDrinkB[i] <= 105
#

class Solution(object):
    def maxEnergyBoost(self, energyDrinkA, energyDrinkB):
        """
        :type energyDrinkA: List[int]
        :type energyDrinkB: List[int]
        :rtype: int
        """
        n = len(energyDrinkA)
        dp = [[0] * 3 for _ in range(n)]

        dp[0][0] = energyDrinkA[0]
        dp[0][1] = energyDrinkB[0]
        dp[0][2] = 0

        for i in range(1, n):
            dp[i][0] = max(dp[i-1][0], dp[i-1][2]) + energyDrinkA[i]
            dp[i][1] = max(dp[i-1][1], dp[i-1][2]) + energyDrinkB[i]
            dp[i][2] = max(dp[i-1][0], dp[i-1][1], dp[i-1][2])

        return max(dp[n-1])