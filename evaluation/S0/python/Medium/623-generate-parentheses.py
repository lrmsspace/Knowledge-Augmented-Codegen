# Source: https://leetcode.com/problems/generate-parentheses/   |   Difficulty: Medium
#
# Problem Description:
# Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
#
# Example:
# Input: n = 3
# Output: ["((()))","(()())","(())()","()(())","()()()"]
#
# Constraints:
# 1 <= n <= 8
#

class Solution(object):
    def generateParenthesis(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        res = []
        
        def backtrack(s='', left=0, right=0):
            if len(s) == 2 * n:
                res.append(s)
                return
            if left < n:
                backtrack(s + '(', left + 1, right)
            if right < left:
                backtrack(s + ')', left, right + 1)
        
        backtrack()
        return res