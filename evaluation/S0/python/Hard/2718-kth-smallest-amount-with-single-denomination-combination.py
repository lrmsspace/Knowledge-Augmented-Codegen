# Source: https://leetcode.com/problems/kth-smallest-amount-with-single-denomination-combination/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array coins representing coins of different denominations and an integer k.
#
# You have an infinite number of coins of each denomination. However, you are not allowed to combine coins of different denominations.
#
# Return the kth smallest amount that can be made using these coins.
#
# Example:
# Input: coins = [3,6,9], k = 3
#
# Output:  9
#
# Explanation: The given coins can make the following amounts:
# Coin 3 produces multiples of 3: 3, 6, 9, 12, 15, etc.
# Coin 6 produces multiples of 6: 6, 12, 18, 24, etc.
# Coin 9 produces multiples of 9: 9, 18, 27, 36, etc.
# All of the coins combined produce: 3, 6, 9, 12, 15, etc.
#
# Constraints:
# 1 <= coins.length <= 15
# 	1 <= coins[i] <= 25
# 	1 <= k <= 2 * 109
# 	coins contains pairwise distinct integers.
#

class Solution(object):
    def findKthSmallest(self, coins, k):
        """
        :type coins: List[int]
        :type k: int
        :rtype: int
        """
        import heapq

        min_heap = []
        for coin in coins:
            heapq.heappush(min_heap, (coin, coin))

        count = 0
        while min_heap:
            amount, coin = heapq.heappop(min_heap)
            count += 1
            if count == k:
                return amount
            heapq.heappush(min_heap, (amount + coin, coin))