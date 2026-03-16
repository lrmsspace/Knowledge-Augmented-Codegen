# Source: https://leetcode.com/problems/maximize-palindrome-length-from-subsequences/   |   Difficulty: Hard
#
# Problem Description:
# You are given two strings, word1 and word2. You want to construct a string in the following manner:
#
#
# 	Choose some non-empty subsequence subsequence1 from word1.
# 	Choose some non-empty subsequence subsequence2 from word2.
# 	Concatenate the subsequences: subsequence1 + subsequence2, to make the string.
#
#
# Return the length of the longest palindrome that can be constructed in the described manner. If no palindromes can be constructed, return 0.
#
# A subsequence of a string s is a string that can be made by deleting some (possibly none) characters from s without changing the order of the remaining characters.
#
# A palindrome is a string that reads the same forward as well as backward.
#
# Example:
# Input: word1 = "cacb", word2 = "cbba"
# Output: 5
# Explanation: Choose "ab" from word1 and "cba" from word2 to make "abcba", which is a palindrome.
#
# Constraints:
# 1 <= word1.length, word2.length <= 1000
# 	word1 and word2 consist of lowercase English letters.
#

class Solution(object):
    def longestPalindrome(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        n, m = len(word1), len(word2)
        dp = [[0] * (m + 1) for _ in range(n + 1)]
        
        for i in range(1, n + 1):
            for j in range(1, m + 1):
                if word1[i - 1] == word2[j - 1]:
                    dp[i][j] = 2
                    for x in range(i - 1):
                        for y in range(j - 1):
                            if word1[x] == word2[y]:
                                dp[i][j] = max(dp[i][j], dp[x + 1][y + 1] + 2)
                else:
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
        
        return dp[n][m]