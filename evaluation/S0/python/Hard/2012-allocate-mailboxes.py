# Source: https://leetcode.com/problems/allocate-mailboxes/   |   Difficulty: Hard
#
# Problem Description:
# Given the array houses where houses[i] is the location of the ith house along a street and an integer k, allocate k mailboxes in the street.
#
# Return the minimum total distance between each house and its nearest mailbox.
#
# The test cases are generated so that the answer fits in a 32-bit integer.
#
# Example:
# Input: houses = [1,4,8,10,20], k = 3
# Output: 5
# Explanation: Allocate mailboxes in position 3, 9 and 20.
# Minimum total distance from each houses to nearest mailboxes is |3-1| + |4-3| + |9-8| + |10-9| + |20-20| = 5
#
# Constraints:
# 1 <= k <= houses.length <= 100
# 	1 <= houses[i] <= 104
# 	All the integers of houses are unique.
#

class Solution(object):
    def minDistance(self, houses, k):
        """
        :type houses: List[int]
        :type k: int
        :rtype: int
        """
        n = len(houses)
        houses.sort()

        # Precompute cost for placing one mailbox between houses[i] and houses[j]
        cost = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(i, n):
                median = houses[(i + j) // 2]
                cost[i][j] = sum(abs(houses[x] - median) for x in range(i, j + 1))

        # DP to find minimum distance with k mailboxes
        dp = [[float('inf')] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 0

        for i in range(1, n + 1):
            for m in range(1, min(i, k) + 1):
                for j in range(i):
                    dp[i][m] = min(dp[i][m], dp[j][m - 1] + cost[j][i - 1])

        return dp[n][k]