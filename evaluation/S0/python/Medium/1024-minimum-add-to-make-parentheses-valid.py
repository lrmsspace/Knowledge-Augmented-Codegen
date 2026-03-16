# Source: https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/   |   Difficulty: Medium
#
# Problem Description:
# A parentheses string is valid if and only if:
#
#
# 	It is the empty string,
# 	It can be written as AB (A concatenated with B), where A and B are valid strings, or
# 	It can be written as (A), where A is a valid string.
#
#
# You are given a parentheses string s. In one move, you can insert a parenthesis at any position of the string.
#
#
# 	For example, if s = "()))", you can insert an opening parenthesis to be "(()))" or a closing parenthesis to be "())))".
#
#
# Return the minimum number of moves required to make s valid.
#
# Example:
# Input: s = "())"
# Output: 1
#
# Constraints:
# 1 <= s.length <= 1000
# 	s[i] is either '(' or ')'.
#

class Solution(object):
    def minAddToMakeValid(self, s):
        """
        :type s: str
        :rtype: int
        """
        left_unmatched = 0
        right_unmatched = 0
        
        for char in s:
            if char == '(':
                left_unmatched += 1
            elif char == ')':
                if left_unmatched > 0:
                    left_unmatched -= 1
                else:
                    right_unmatched += 1
        
        return left_unmatched + right_unmatched