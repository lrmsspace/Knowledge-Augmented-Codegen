# Source: https://leetcode.com/problems/longest-valid-parentheses/   |   Difficulty: Hard
#
# Problem Description:
# Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses substring.
#
# Example:
# Input: s = "(()"
# Output: 2
# Explanation: The longest valid parentheses substring is "()".
#
# Constraints:
# 0 <= s.length <= 3 * 104
# 	s[i] is '(', or ')'.
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
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        max_length = 0
        stack = [-1]  # Initialize stack with a base index for valid substring calculation

        for i, char in enumerate(s):
            if char == '(':
                stack.append(i)  # Push the index of the '(' onto the stack
            else:
                stack.pop()  # Pop the last '(' index
                if not stack:
                    stack.append(i)  # If stack is empty, push the current index as a new base
                else:
                    max_length = max(max_length, i - stack[-1])  # Calculate valid substring length

        return max_length