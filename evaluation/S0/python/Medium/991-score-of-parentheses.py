# Source: https://leetcode.com/problems/score-of-parentheses/   |   Difficulty: Medium
#
# Problem Description:
# Given a balanced parentheses string s, return the score of the string.
#
# The score of a balanced parentheses string is based on the following rule:
#
#
# 	"()" has score 1.
# 	AB has score A + B, where A and B are balanced parentheses strings.
# 	(A) has score 2 * A, where A is a balanced parentheses string.
#
# Example:
# Input: s = "()"
# Output: 1
#
# Constraints:
# 2 <= s.length <= 50
# 	s consists of only '(' and ')'.
# 	s is a balanced parentheses string.
#

class Solution(object):
    def scoreOfParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        stack = []
        for char in s:
            if char == '(':
                stack.append(0)
            else:
                v = stack.pop()
                if v == 0:
                    stack.append(1)
                else:
                    stack.append(stack.pop() + 2 * v)
        return sum(stack)