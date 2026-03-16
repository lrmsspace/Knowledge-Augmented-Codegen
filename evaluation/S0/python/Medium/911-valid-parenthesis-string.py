# Source: https://leetcode.com/problems/valid-parenthesis-string/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s containing only three types of characters: '(', ')' and '*', return true if s is valid.
#
# The following rules define a valid string:
#
#
# 	Any left parenthesis '(' must have a corresponding right parenthesis ')'.
# 	Any right parenthesis ')' must have a corresponding left parenthesis '('.
# 	Left parenthesis '(' must go before the corresponding right parenthesis ')'.
# 	'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".
#
# Example:
# Input: s = "()"
# Output: true
#
# Constraints:
# 1 <= s.length <= 100
# 	s[i] is '(', ')' or '*'.
#

class Solution(object):
    def checkValidString(self, s):
        """
        :type s: str
        :rtype: bool
        """
        low = 0  # 最小可能的左括号数量
        high = 0 # 最大可能的左括号数量

        for char in s:
            if char == '(':
                low += 1
                high += 1
            elif char == ')':
                low = max(low - 1, 0)
                high -= 1
            else:  # char == '*'
                low = max(low - 1, 0)
                high += 1

            if high < 0:
                return False

        return low == 0