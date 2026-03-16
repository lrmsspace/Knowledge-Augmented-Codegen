# Source: https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/   |   Difficulty: Hard
#
# Problem Description:
# You are given three integers n, m and k. Consider the following algorithm to find the maximum element of an array of positive integers:
#
# You should build the array arr which has the following properties:
#
#
# 	arr has exactly n integers.
# 	1 <= arr[i] <= m where (0 <= i < n).
# 	After applying the mentioned algorithm to arr, the value search_cost is equal to k.
#
#
# Return the number of ways to build the array arr under the mentioned conditions. As the answer may grow large, the answer must be computed modulo 109 + 7.
#
# Example:
# Input: n = 2, m = 3, k = 1
# Output: 6
# Explanation: The possible arrays are [1, 1], [2, 1], [2, 2], [3, 1], [3, 2] [3, 3]
#
# Constraints:
# 1 <= n <= 50
# 	1 <= m <= 100
# 	0 <= k <= n
#

class Solution(object):
    def numOfArrays(self, n, m, k):
        """
        :type n: int
        :type m: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        dp = [[[0] * (k + 1) for _ in range(m + 1)] for _ in range(n + 1)]
        
        for j in range(1, m + 1):
            dp[1][j][1] = 1
        
        for i in range(2, n + 1):
            for j in range(1, m + 1):
                for p in range(1, k + 1):
                    dp[i][j][p] = (dp[i - 1][j][p] * j) % MOD
                    for x in range(1, j):
                        dp[i][j][p] = (dp[i][j][p] + dp[i - 1][x][p - 1]) % MOD
        
        result = 0
        for j in range(1, m + 1):
            result = (result + dp[n][j][k]) % MOD
        
        return result