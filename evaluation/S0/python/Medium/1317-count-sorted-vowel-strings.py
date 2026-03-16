# Source: https://leetcode.com/problems/count-sorted-vowel-strings/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted.
#
# A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet.
#
# Example:
# Input: n = 1
# Output: 5
# Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
#
# Constraints:
# 1 <= n <= 50
#

class Solution(object):
    def countVowelStrings(self, n):
        """
        :type n: int
        :rtype: int
        """
        # 使用动态规划来解决问题
        # dp[i][j] 表示长度为 i 且以第 j 个元音字母结尾的字符串数量
        dp = [[0] * 5 for _ in range(n + 1)]
        
        # 初始化长度为 1 的字符串
        for j in range(5):
            dp[1][j] = j + 1
        
        # 填充 dp 表
        for i in range(2, n + 1):
            for j in range(5):
                dp[i][j] = sum(dp[i - 1][k] for k in range(j + 1))
        
        # 计算总数
        return sum(dp[n])