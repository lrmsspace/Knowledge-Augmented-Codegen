# Source: https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/   |   Difficulty: Medium
#
# Problem Description:
# Given n points on a 1-D plane, where the ith point (from 0 to n-1) is at x = i, find the number of ways we can draw exactly k non-overlapping line segments such that each segment covers two or more points. The endpoints of each segment must have integral coordinates. The k line segments do not have to cover all n points, and they are allowed to share endpoints.
#
# Return the number of ways we can draw k non-overlapping line segments. Since this number can be huge, return it modulo 109 + 7.
#
# Example:
# Input: n = 4, k = 2
# Output: 5
# Explanation: The two line segments are shown in red and blue.
# The image above shows the 5 different ways {(0,2),(2,3)}, {(0,1),(1,3)}, {(0,1),(2,3)}, {(1,2),(2,3)}, {(0,1),(1,2)}.
#
# Constraints:
# 2 <= n <= 1000
# 	1 <= k <= n-1
#

class Solution(object):
    def numberOfSets(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        
        for i in range(1, n + 1):
            dp[i][0] = 1  # Base case: one way to draw 0 segments
        
        for i in range(1, n + 1):
            for j in range(1, min(i // 2, k) + 1):
                dp[i][j] = (dp[i - 1][j] + dp[i - 2][j - 1]) % MOD
        
        return dp[n][k]