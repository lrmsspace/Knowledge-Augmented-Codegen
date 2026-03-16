# Source: https://leetcode.com/problems/reverse-only-letters/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s, reverse the string according to the following rules:
#
#
# 	All the characters that are not English letters remain in the same position.
# 	All the English letters (lowercase or uppercase) should be reversed.
#
#
# Return s after reversing it.
#
# Example:
# Input: s = "ab-cd"
# Output: "dc-ba"
#
# Constraints:
# 1 <= s.length <= 100
# 	s consists of characters with ASCII values in the range [33, 122].
# 	s does not contain '\"' or '\\'.
#

class Solution(object):
    def reverseOnlyLetters(self, s):
        """
        :type s: str
        :rtype: str
        """
        letters = [c for c in s if c.isalpha()]
        result = []
        for c in s:
            if c.isalpha():
                result.append(letters.pop())
            else:
                result.append(c)
        return ''.join(result)