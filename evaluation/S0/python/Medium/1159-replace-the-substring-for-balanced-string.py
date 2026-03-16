# Source: https://leetcode.com/problems/replace-the-substring-for-balanced-string/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s of length n containing only four kinds of characters: 'Q', 'W', 'E', and 'R'.
#
# A string is said to be balanced if each of its characters appears n / 4 times where n is the length of the string.
#
# Return the minimum length of the substring that can be replaced with any other string of the same length to make s balanced. If s is already balanced, return 0.
#
# Example:
# Input: s = "QWER"
# Output: 0
# Explanation: s is already balanced.
#
# Constraints:
# n == s.length
# 	4 <= n <= 105
# 	n is a multiple of 4.
# 	s contains only 'Q', 'W', 'E', and 'R'.
#

class Solution(object):
    def balancedString(self, s):
        """
        :type s: str
        :rtype: int
        """
        from collections import Counter

        n = len(s)
        count = Counter(s)
        required = n // 4
        left = 0
        min_length = n

        for right in range(n):
            count[s[right]] -= 1

            while left < n and all(count[char] <= required for char in 'QWER'):
                min_length = min(min_length, right - left + 1)
                count[s[left]] += 1
                left += 1

        return min_length