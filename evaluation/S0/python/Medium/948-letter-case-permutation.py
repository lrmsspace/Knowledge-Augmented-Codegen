# Source: https://leetcode.com/problems/letter-case-permutation/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, you can transform every letter individually to be lowercase or uppercase to create another string.
#
# Return a list of all possible strings we could create. Return the output in any order.
#
# Example:
# Input: s = "a1b2"
# Output: ["a1b2","a1B2","A1b2","A1B2"]
#
# Constraints:
# 1 <= s.length <= 12
# 	s consists of lowercase English letters, uppercase English letters, and digits.
#

class Solution(object):
    def letterCasePermutation(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        res = []
        def backtrack(sub="", i=0):
            if i == len(s):
                res.append(sub)
            else:
                if s[i].isalpha():
                    backtrack(sub + s[i].lower(), i + 1)
                    backtrack(sub + s[i].upper(), i + 1)
                else:
                    backtrack(sub + s[i], i + 1)
        backtrack()
        return res