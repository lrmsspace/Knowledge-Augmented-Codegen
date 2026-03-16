# Source: https://leetcode.com/problems/remove-duplicate-letters/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
#
# Example:
# Input: s = "bcabc"
# Output: "abc"
#
# Constraints:
# 1 <= s.length <= 104
# 	s consists of lowercase English letters.
#
#
#  
# Note: This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
#

class Solution(object):
    def removeDuplicateLetters(self, s):
        """
        :type s: str
        :rtype: str
        """
        last_occurrence = {c: i for i, c in enumerate(s)}
        stack = []
        in_stack = set()

        for i, c in enumerate(s):
            if c in in_stack:
                continue

            while stack and c < stack[-1] and i < last_occurrence[stack[-1]]:
                removed_char = stack.pop()
                in_stack.remove(removed_char)

            stack.append(c)
            in_stack.add(c)

        return ''.join(stack)