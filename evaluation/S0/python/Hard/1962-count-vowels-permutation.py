# Source: https://leetcode.com/problems/count-vowels-permutation/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer n, your task is to count how many strings of length n can be formed under the following rules:
#
#
# 	Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
# 	Each vowel 'a' may only be followed by an 'e'.
# 	Each vowel 'e' may only be followed by an 'a' or an 'i'.
# 	Each vowel 'i' may not be followed by another 'i'.
# 	Each vowel 'o' may only be followed by an 'i' or a 'u'.
# 	Each vowel 'u' may only be followed by an 'a'.
#
#
# Since the answer may be too large, return it modulo 10^9 + 7.
#
# Example:
# Input: n = 1
# Output: 5
# Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
#
# Constraints:
# 1 <= n <= 2 * 10^4
#

class Solution(object):
    def countVowelPermutation(self, n):
        """
        :type n: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        # dp[i][j]: 长度为 i 且以 j 结尾的字符串数量
        dp = [[0] * 5 for _ in range(n + 1)]
        
        # 初始化长度为 1 的字符串
        for j in range(5):
            dp[1][j] = 1
        
        for i in range(2, n + 1):
            dp[i][0] = (dp[i-1][1] + dp[i-1][2] + dp[i-1][4]) % MOD  # 'a' 后接 'e', 'i', 'u'
            dp[i][1] = (dp[i-1][0] + dp[i-1][2]) % MOD               # 'e' 后接 'a', 'i'
            dp[i][2] = (dp[i-1][1] + dp[i-1][3]) % MOD               # 'i' 后接 'e', 'o'
            dp[i][3] = dp[i-1][2] % MOD                               # 'o' 后接 'i'
            dp[i][4] = (dp[i-1][2] + dp[i-1][3]) % MOD               # 'u' 后接 'i', 'o'
        
        return sum(dp[n]) % MOD