# Source: https://leetcode.com/problems/palindrome-partitioning-iii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s containing lowercase letters and an integer k. You need to :
#
#
# 	First, change some characters of s to other lowercase English letters.
# 	Then divide s into k non-empty disjoint substrings such that each substring is a palindrome.
#
#
# Return the minimal number of characters that you need to change to divide the string.
#
# Example:
# Input: s = "abc", k = 2
# Output: 1
# Explanation: You can split the string into "ab" and "c", and change 1 character in "ab" to make it palindrome.
#
# Constraints:
# 1 <= k <= s.length <= 100.
# 	s only contains lowercase English letters.
#

class Solution(object):
    def palindromePartition(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        n = len(s)
        # Precompute the cost to convert any substring s[i:j+1] into a palindrome
        cost = [[0] * n for _ in range(n)]
        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                cost[i][j] = cost[i + 1][j - 1] + (s[i] != s[j])

        # DP array to store the minimum changes needed for first i characters with j partitions
        dp = [[float('inf')] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 0

        for i in range(1, n + 1):
            for j in range(1, min(i, k) + 1):
                for p in range(i):
                    dp[i][j] = min(dp[i][j], dp[p][j - 1] + cost[p][i - 1])

        return dp[n][k]