# Source: https://leetcode.com/problems/longest-ideal-subsequence/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s consisting of lowercase letters and an integer k. We call a string t ideal if the following conditions are satisfied:
#
#
# 	t is a subsequence of the string s.
# 	The absolute difference in the alphabet order of every two adjacent letters in t is less than or equal to k.
#
#
# Return the length of the longest ideal string.
#
# A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
#
# Note that the alphabet order is not cyclic. For example, the absolute difference in the alphabet order of 'a' and 'z' is 25, not 1.
#
# Example:
# Input: s = "acfgbd", k = 2
# Output: 4
# Explanation: The longest ideal string is "acbd". The length of this string is 4, so 4 is returned.
# Note that "acfgbd" is not ideal because 'c' and 'f' have a difference of 3 in alphabet order.
#
# Constraints:
# 1 <= s.length <= 105
# 	0 <= k <= 25
# 	s consists of lowercase English letters.
#

class Solution(object):
    def longestIdealString(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        dp = [0] * 26  # dp[i] 表示以字母 chr(i + ord('a')) 结尾的最长理想子序列长度

        for char in s:
            index = ord(char) - ord('a')
            start = max(0, index - k)
            end = min(25, index + k)

            max_length = 0
            for j in range(start, end + 1):
                max_length = max(max_length, dp[j])

            dp[index] = max(dp[index], max_length + 1)

        return max(dp)