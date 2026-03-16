# Source: https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s that consists of lower case English letters and brackets.
#
# Reverse the strings in each pair of matching parentheses, starting from the innermost one.
#
# Your result should not contain any brackets.
#
# Example:
# Input: s = "(abcd)"
# Output: "dcba"
#
# Constraints:
# 1 <= s.length <= 2000
# 	s only contains lower case English characters and parentheses.
# 	It is guaranteed that all parentheses are balanced.
#

class Solution(object):
    def reverseParentheses(self, s):
        """
        :type s: str
        :rtype: str
        """
        stack = []
        for char in s:
            if char == ')':
                temp = []
                while stack and stack[-1] != '(':
                    temp.append(stack.pop())
                stack.pop()  # Remove the '(' from the stack
                stack.extend(temp)  # Add the reversed substring back to the stack
            else:
                stack.append(char)
        return ''.join(stack)