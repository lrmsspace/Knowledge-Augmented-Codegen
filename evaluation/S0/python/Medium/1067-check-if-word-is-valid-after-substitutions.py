# Source: https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, determine if it is valid.
#
# A string s is valid if, starting with an empty string t = "", you can transform t into s after performing the following operation any number of times:
#
#
# 	Insert string "abc" into any position in t. More formally, t becomes tleft + "abc" + tright, where t == tleft + tright. Note that tleft and tright may be empty.
#
#
# Return true if s is a valid string, otherwise, return false.
#
# Example:
# Input: s = "aabcbc"
# Output: true
# Explanation:
# "" -> "abc" -> "aabcbc"
# Thus, "aabcbc" is valid.
#
# Constraints:
# 1 <= s.length <= 2 * 104
# 	s consists of letters 'a', 'b', and 'c'
#

class Solution(object):
    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        stack = []
        
        for char in s:
            if char == 'c':
                if len(stack) < 2 or stack[-1] != 'b' or stack[-2] != 'a':
                    return False
                stack.pop()  # Remove 'b'
                stack.pop()  # Remove 'a'
            else:
                stack.append(char)
        
        return len(stack) == 0