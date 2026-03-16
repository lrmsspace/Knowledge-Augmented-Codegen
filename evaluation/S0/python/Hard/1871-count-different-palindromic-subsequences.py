# Source: https://leetcode.com/problems/count-different-palindromic-subsequences/   |   Difficulty: Hard
#
# Problem Description:
# Given a string s, return the number of different non-empty palindromic subsequences in s. Since the answer may be very large, return it modulo 109 + 7.
#
# A subsequence of a string is obtained by deleting zero or more characters from the string.
#
# A sequence is palindromic if it is equal to the sequence reversed.
#
# Two sequences a1, a2, ... and b1, b2, ... are different if there is some i for which ai != bi.
#
# Example:
# Input: s = "bccb"
# Output: 6
# Explanation: The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
# Note that 'bcb' is counted only once, even though it occurs twice.
#
# Constraints:
# 1 <= s.length <= 1000
# 	s[i] is either 'a', 'b', 'c', or 'd'.
#

class Solution(object):
    def countPalindromicSubsequences(self, s):
        """
        :type s: str
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(s)
        dp = [[0] * n for _ in range(n)]

        for i in range(n-1, -1, -1):
            dp[i][i] = 1
            for j in range(i+1, n):
                if s[i] == s[j]:
                    low, high = i + 1, j - 1
                    while low <= high and s[low] != s[i]:
                        low += 1
                    while low <= high and s[high] != s[j]:
                        high -= 1
                    if low > high:
                        dp[i][j] = dp[i+1][j-1] * 2 + 2
                    elif low == high:
                        dp[i][j] = dp[i+1][j-1] * 2 + 1
                    else:
                        dp[i][j] = dp[i+1][j-1] * 2 - dp[low+1][high-1]
                else:
                    dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1]
                dp[i][j] = (dp[i][j] + MOD) % MOD

        return dp[0][n-1]