# Source: https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/   |   Difficulty: Hard
#
# Problem Description:
# You are given three integers n, m, k. A good array arr of size n is defined as follows:
#
#
# 	Each element in arr is in the inclusive range [1, m].
# 	Exactly k indices i (where 1 <= i < n) satisfy the condition arr[i - 1] == arr[i].
#
#
# Return the number of good arrays that can be formed.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: n = 3, m = 2, k = 1
#
# Output: 4
#
# Explanation:
#
#
# 	There are 4 good arrays. They are [1, 1, 2], [1, 2, 2], [2, 1, 1] and [2, 2, 1].
# 	Hence, the answer is 4.
#
# Constraints:
# 1 <= n <= 105
# 	1 <= m <= 105
# 	0 <= k <= n - 1
#

class Solution(object):
    def countGoodArrays(self, n, m, k):
        """
        :type n: int
        :type m: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        # dp[i][j]: number of arrays of length i with j matching adjacent elements
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        
        # Base case: arrays of length 1
        for j in range(k + 1):
            dp[1][j] = 0
        dp[1][0] = m
        
        for i in range(2, n + 1):
            for j in range(0, min(i - 1, k) + 1):
                # Case 1: arr[i-1] != arr[i-2]
                dp[i][j] = dp[i - 1][j] * (m - 1) % MOD
                
                # Case 2: arr[i-1] == arr[i-2]
                if j > 0:
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD
        
        return dp[n][k]