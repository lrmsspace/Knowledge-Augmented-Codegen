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

class Solution(object):
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        max_length = 0
        stack = [-1]  # Initialize stack with -1 to handle base case

        for i in range(len(s)):
            if s[i] == '(':
                stack.append(i)
            else:
                stack.pop()
                if not stack:
                    stack.append(i)
                else:
                    max_length = max(max_length, i - stack[-1])

        return max_length