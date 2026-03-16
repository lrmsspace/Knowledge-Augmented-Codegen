# Source: https://leetcode.com/problems/isomorphic-strings/   |   Difficulty: Easy
#
# Problem Description:
# Given two strings s and t, determine if they are isomorphic.
#
# Two strings s and t are isomorphic if the characters in s can be replaced to get t.
#
# All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.
#
# Example:
# Input: s = "egg", t = "add"
#
# Output: true
#
# Explanation:
#
# The strings s and t can be made identical by:
#
#
# 	Mapping 'e' to 'a'.
# 	Mapping 'g' to 'd'.
#
# Constraints:
# 1 <= s.length <= 5 * 104
# 	t.length == s.length
# 	s and t consist of any valid ascii character.
#

class Solution(object):
    def isIsomorphic(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: bool
        """
        def build_map(string):
            char_map = {}
            mapped_chars = set()
            result = []
            
            for char in string:
                if char not in char_map:
                    for c in range(256):  # Assuming ASCII characters
                        candidate = chr(c)
                        if candidate not in mapped_chars:
                            char_map[char] = candidate
                            mapped_chars.add(candidate)
                            break
                result.append(char_map[char])
            return ''.join(result)
        
        return build_map(s) == build_map(t)