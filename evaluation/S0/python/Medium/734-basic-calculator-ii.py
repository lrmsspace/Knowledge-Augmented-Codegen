# Source: https://leetcode.com/problems/basic-calculator-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s which represents an expression, evaluate this expression and return its value. 
#
# The integer division should truncate toward zero.
#
# You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].
#
# Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().
#
# Example:
# Input: s = "3+2*2"
# Output: 7
#
# Constraints:
# 1 <= s.length <= 3 * 105
# 	s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
# 	s represents a valid expression.
# 	All the integers in the expression are non-negative integers in the range [0, 231 - 1].
# 	The answer is guaranteed to fit in a 32-bit integer.
#

class Solution(object):
    def calculate(self, s):
        """
        :type s: str
        :rtype: int
        """
        stack = []
        num = 0
        sign = '+'
        s += '+'
        
        for c in s:
            if c.isdigit():
                num = num * 10 + int(c)
            elif c in '+-*/':
                if sign == '+':
                    stack.append(num)
                elif sign == '-':
                    stack.append(-num)
                elif sign == '*':
                    stack[-1] = stack[-1] * num
                elif sign == '/':
                    stack[-1] = int(stack[-1] / num)
                
                sign = c
                num = 0
        
        return sum(stack)