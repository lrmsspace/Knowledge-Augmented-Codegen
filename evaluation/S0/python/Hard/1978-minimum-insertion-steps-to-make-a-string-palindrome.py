# Source: https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/   |   Difficulty: Hard
#
# Problem Description:
# Given a string s. In one step you can insert any character at any index of the string.
#
# Return the minimum number of steps to make s palindrome.
#
# A Palindrome String is one that reads the same backward as well as forward.
#
# Example:
# Input: s = "zzazz"
# Output: 0
# Explanation: The string "zzazz" is already palindrome we do not need any insertions.
#
# Constraints:
# 1 <= s.length <= 500
# 	s consists of lowercase English letters.
#

class Solution(object):
    def minInsertions(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        dp = [[0] * n for _ in range(n)]

        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                if s[i] == s[j]:
                    dp[i][j] = dp[i + 1][j - 1]
                else:
                    dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1

        return dp[0][n - 1]