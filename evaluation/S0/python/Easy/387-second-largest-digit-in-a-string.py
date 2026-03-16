# Source: https://leetcode.com/problems/second-largest-digit-in-a-string/   |   Difficulty: Easy
#
# Problem Description:
# Given an alphanumeric string s, return the second largest numerical digit that appears in s, or -1 if it does not exist.
#
# An alphanumeric string is a string consisting of lowercase English letters and digits.
#
# Example:
# Input: s = "dfa12321afd"
# Output: 2
# Explanation: The digits that appear in s are [1, 2, 3]. The second largest digit is 2.
#
# Constraints:
# 1 <= s.length <= 500
# 	s consists of only lowercase English letters and digits.
#

class Solution(object):
    def secondHighest(self, s):
        """
        :type s: str
        :rtype: int
        """
        digits = set()
        for char in s:
            if char.isdigit():
                digits.add(int(char))
        if len(digits) < 2:
            return -1
        sorted_digits = sorted(digits, reverse=True)
        return sorted_digits[1]