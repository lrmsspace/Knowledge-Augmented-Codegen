# Source: https://leetcode.com/problems/number-of-beautiful-partitions/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s that consists of the digits '1' to '9' and two integers k and minLength.
#
# A partition of s is called beautiful if:
#
#
# 	s is partitioned into k non-intersecting substrings.
# 	Each substring has a length of at least minLength.
# 	Each substring starts with a prime digit and ends with a non-prime digit. Prime digits are '2', '3', '5', and '7', and the rest of the digits are non-prime.
#
#
# Return the number of beautiful partitions of s. Since the answer may be very large, return it modulo 109 + 7.
#
# A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: s = "23542185131", k = 3, minLength = 2
# Output: 3
# Explanation: There exists three ways to create a beautiful partition:
# "2354 | 218 | 5131"
# "2354 | 21851 | 31"
# "2354218 | 51 | 31"
#
# Constraints:
# 1 <= k, minLength <= s.length <= 1000
# 	s consists of the digits '1' to '9'.
#

class Solution(object):
    def beautifulPartitions(self, s, k, minLength):
        """
        :type s: str
        :type k: int
        :type minLength: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(s)
        primes = {'2', '3', '5', '7'}
        
        if s[0] not in primes or s[-1] in primes:
            return 0
        
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 1
        
        for i in range(1, n + 1):
            for j in range(k + 1):
                dp[i][j] = dp[i - 1][j]
                
                if j > 0 and i >= minLength:
                    if s[i - minLength] in primes and s[i - 1] not in primes:
                        dp[i][j] = (dp[i][j] + dp[i - minLength][j - 1]) % MOD
        
        return dp[n][k]