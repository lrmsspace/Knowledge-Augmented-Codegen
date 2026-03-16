# Source: https://leetcode.com/problems/count-substrings-starting-and-ending-with-given-character/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s and a character c. Return the total number of substrings of s that start and end with c.
#
# Example:
# Input: s = "abada", c = "a"
#
# Output: 6
#
# Explanation: Substrings starting and ending with "a" are: "abada", "abada", "abada", "abada", "abada", "abada".
#
# Constraints:
# 1 <= s.length <= 105
# 	s and c consist only of lowercase English letters.
#

class Solution(object):
    def countSubstrings(self, s, c):
        """
        :type s: str
        :type c: str
        :rtype: int
        """
        count = 0
        n = len(s)
        
        # Count occurrences of character c in the string s
        for char in s:
            if char == c:
                count += 1
        
        # The number of substrings that start and end with c
        # is given by the formula: count * (count + 1) // 2
        return count * (count + 1) // 2