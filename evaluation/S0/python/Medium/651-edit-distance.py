# Source: https://leetcode.com/problems/edit-distance/   |   Difficulty: Medium
#
# Problem Description:
# Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
#
# You have the following three operations permitted on a word:
#
#
# 	Insert a character
# 	Delete a character
# 	Replace a character
#
# Example:
# Input: word1 = "horse", word2 = "ros"
# Output: 3
# Explanation: 
# horse -> rorse (replace 'h' with 'r')
# rorse -> rose (remove 'r')
# rose -> ros (remove 'e')
#
# Constraints:
# 0 <= word1.length, word2.length <= 500
# 	word1 and word2 consist of lowercase English letters.
#

class Solution(object):
    def minDistance(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        m, n = len(word1), len(word2)
        dp = [[0] * (n + 1) for _ in range(m + 1)]

        for i in range(m + 1):
            dp[i][0] = i
        for j in range(n + 1):
            dp[0][j] = j

        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if word1[i - 1] == word2[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1]
                else:
                    dp[i][j] = min(dp[i - 1][j] + 1,    # 删除
                                   dp[i][j - 1] + 1,    # 插入
                                   dp[i - 1][j - 1] + 1) # 替换

        return dp[m][n]