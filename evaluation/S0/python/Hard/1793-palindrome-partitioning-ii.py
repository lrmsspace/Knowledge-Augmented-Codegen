# Source: https://leetcode.com/problems/palindrome-partitioning-ii/   |   Difficulty: Hard
#
# Problem Description:
# Given a string s, partition s such that every substring of the partition is a palindrome.
#
# Return the minimum cuts needed for a palindrome partitioning of s.
#
# Example:
# Input: s = "aab"
# Output: 1
# Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
#
# Constraints:
# 1 <= s.length <= 2000
# 	s consists of lowercase English letters only.
#

class Solution(object):
    def minCut(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        dp = [0] * n
        pal = [[False] * n for _ in range(n)]

        for i in range(n):
            min_cuts = i
            for j in range(i + 1):
                if s[j] == s[i] and (i - j < 2 or pal[j + 1][i - 1]):
                    pal[j][i] = True
                    min_cuts = 0 if j == 0 else min(min_cuts, dp[j - 1] + 1)
            dp[i] = min_cuts

        return dp[-1]