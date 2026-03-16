# Source: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s of '(' , ')' and lowercase English characters.
#
# Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.
#
# Formally, a parentheses string is valid if and only if:
#
#
# 	It is the empty string, contains only lowercase characters, or
# 	It can be written as AB (A concatenated with B), where A and B are valid strings, or
# 	It can be written as (A), where A is a valid string.
#
# Example:
# Input: s = "lee(t(c)o)de)"
# Output: "lee(t(c)o)de"
# Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is either '(' , ')', or lowercase English letter.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minRemoveToMakeValid(self, s):
        """
        :type s: str
        :rtype: str
        """
        s = list(s)
        stack = []
        
        for i, char in enumerate(s):
            if char == '(':
                stack.append(i)
            elif char == ')':
                if stack:
                    stack.pop()
                else:
                    s[i] = ''
        
        for i in stack:
            s[i] = ''
        
        return ''.join(s)