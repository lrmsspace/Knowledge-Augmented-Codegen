# Source: https://leetcode.com/problems/clear-digits/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s.
#
# Your task is to remove all digits by doing this operation repeatedly:
#
#
# 	Delete the first digit and the closest non-digit character to its left.
#
#
# Return the resulting string after removing all digits.
#
# Note that the operation cannot be performed on a digit that does not have any non-digit character to its left.
#
# Example:
# Input: s = "abc"
#
# Output: "abc"
#
# Explanation:
#
# There is no digit in the string.
#
# Constraints:
# 1 <= s.length <= 100
# 	s consists only of lowercase English letters and digits.
# 	The input is generated such that it is possible to delete all digits.
#

class Solution(object):
    def clearDigits(self, s):
        """
        :type s: str
        :rtype: str
        """
        stack = []
        
        for char in s:
            if char.isdigit():
                if stack:
                    stack.pop()  # Remove the closest non-digit character to the left
            else:
                stack.append(char)
        
        return ''.join(stack)