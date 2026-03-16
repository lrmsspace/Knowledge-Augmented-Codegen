# Source: https://leetcode.com/problems/distinct-subsequences-ii/   |   Difficulty: Hard
#
# Problem Description:
# Given a string s, return the number of distinct non-empty subsequences of s. Since the answer may be very large, return it modulo 109 + 7.
# A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not.
#
# Example:
# Input: s = "abc"
# Output: 7
# Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac", "bc", and "abc".
#
# Constraints:
# 1 <= s.length <= 2000
# 	s consists of lowercase English letters.
#

class Solution(object):
    def distinctSubseqII(self, s):
        """
        :type s: str
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(s)
        dp = [0] * (n + 1)
        dp[0] = 1  # 空子序列

        last_occurrence = {}

        for i in range(1, n + 1):
            dp[i] = (2 * dp[i - 1]) % MOD
            char = s[i - 1]

            if char in last_occurrence:
                j = last_occurrence[char]
                dp[i] = (dp[i] - dp[j - 1] + MOD) % MOD

            last_occurrence[char] = i

        return (dp[n] - 1 + MOD) % MOD  # 减去空子序列