# Source: https://leetcode.com/problems/valid-parentheses/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
#
# An input string is valid if:
#
#
# 	Open brackets must be closed by the same type of brackets.
# 	Open brackets must be closed in the correct order.
# 	Every close bracket has a corresponding open bracket of the same type.
#
# Example:
# Input: s = "()"
#
# Output: true
#
# Constraints:
# 1 <= s.length <= 104
# 	s consists of parentheses only '()[]{}'.
#

class Solution(object):
    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        stack = []
        mapping = {")": "(", "}": "{", "]": "["}

        for char in s:
            if char in mapping:
                top_element = stack.pop() if stack else '#'
                if mapping[char] != top_element:
                    return False
            else:
                stack.append(char)

        return not stack