# Source: https://leetcode.com/problems/longest-palindromic-subsequence-after-at-most-k-operations/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s and an integer k.
#
# In one operation, you can replace the character at any position with the next or previous letter in the alphabet (wrapping around so that 'a' is after 'z'). For example, replacing 'a' with the next letter results in 'b', and replacing 'a' with the previous letter results in 'z'. Similarly, replacing 'z' with the next letter results in 'a', and replacing 'z' with the previous letter results in 'y'.
#
# Return the length of the longest palindromic subsequence of s that can be obtained after performing at most k operations.
#
# Example:
# Input: s = "abced", k = 2
#
# Output: 3
#
# Explanation:
#
#
# 	Replace s[1] with the next letter, and s becomes "acced".
# 	Replace s[4] with the previous letter, and s becomes "accec".
#
#
# The subsequence "ccc" forms a palindrome of length 3, which is the maximum.
#
# Constraints:
# 1 <= s.length <= 200
# 	1 <= k <= 200
# 	s consists of only lowercase English letters.
#

class Solution(object):
    def longestPalindromicSubsequence(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        n = len(s)
        dp = [[[0] * (k + 1) for _ in range(n)] for _ in range(n)]

        for length in range(1, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                for ops in range(k + 1):
                    if i == j:
                        dp[i][j][ops] = 1
                    else:
                        if s[i] == s[j]:
                            dp[i][j][ops] = dp[i + 1][j - 1][ops] + 2
                        else:
                            dp[i][j][ops] = max(dp[i + 1][j][ops], dp[i][j - 1][ops])
                            if ops > 0:
                                dp[i][j][ops] = max(dp[i][j][ops], dp[i + 1][j - 1][ops - 1] + 2)

        return dp[0][n - 1][k]