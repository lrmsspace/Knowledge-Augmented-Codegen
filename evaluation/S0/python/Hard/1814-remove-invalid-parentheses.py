# Source: https://leetcode.com/problems/remove-invalid-parentheses/   |   Difficulty: Hard
#
# Problem Description:
# Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.
#
# Return a list of unique strings that are valid with the minimum number of removals. You may return the answer in any order.
#
# Example:
# Input: s = "()())()"
# Output: ["(())()","()()()"]
#
# Constraints:
# 1 <= s.length <= 25
# 	s consists of lowercase English letters and parentheses '(' and ')'.
# 	There will be at most 20 parentheses in s.
#

class Solution(object):
    def removeInvalidParentheses(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        res = []
        level = {s}
        
        while True:
            valid = list(filter(self.isValid, level))
            if valid:
                return valid
            
            next_level = set()
            for item in level:
                for i in range(len(item)):
                    if item[i] in ('(', ')'):
                        next_level.add(item[:i] + item[i+1:])
            level = next_level  