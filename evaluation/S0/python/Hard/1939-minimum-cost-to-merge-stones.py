# Source: https://leetcode.com/problems/minimum-cost-to-merge-stones/   |   Difficulty: Hard
#
# Problem Description:
# There are n piles of stones arranged in a row. The ith pile has stones[i] stones.
#
# A move consists of merging exactly k consecutive piles into one pile, and the cost of this move is equal to the total number of stones in these k piles.
#
# Return the minimum cost to merge all piles of stones into one pile. If it is impossible, return -1.
#
# Example:
# Input: stones = [3,2,4,1], k = 2
# Output: 20
# Explanation: We start with [3, 2, 4, 1].
# We merge [3, 2] for a cost of 5, and we are left with [5, 4, 1].
# We merge [4, 1] for a cost of 5, and we are left with [5, 5].
# We merge [5, 5] for a cost of 10, and we are left with [10].
# The total cost was 20, and this is the minimum possible.
#
# Constraints:
# n == stones.length
# 	1 <= n <= 30
# 	1 <= stones[i] <= 100
# 	2 <= k <= 30
#

class Solution(object):
    def mergeStones(self, stones, k):
        """
        :type stones: List[int]
        :type k: int
        :rtype: int
        """
        n = len(stones)
        if (n - 1) % (k - 1) != 0:
            return -1

        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + stones[i]

        dp = [[[float('inf')] * (k + 1) for _ in range(n)] for _ in range(n)]

        for i in range(n):
            dp[i][i][1] = 0

        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                for m in range(2, k + 1):
                    for mid in range(i, j, k - 1):
                        dp[i][j][m] = min(dp[i][j][m], dp[i][mid][1] + dp[mid + 1][j][m - 1])

                if dp[i][j][k] < float('inf'):
                    dp[i][j][1] = dp[i][j][k] + prefix_sum[j + 1] - prefix_sum[i]

        return dp[0][n - 1][1]