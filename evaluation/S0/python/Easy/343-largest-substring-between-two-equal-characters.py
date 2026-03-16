# Source: https://leetcode.com/problems/largest-substring-between-two-equal-characters/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s, return the length of the longest substring between two equal characters, excluding the two characters. If there is no such substring return -1.
#
# A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: s = "aa"
# Output: 0
# Explanation: The optimal substring here is an empty substring between the two 'a's.
#
# Constraints:
# 1 <= s.length <= 300
# 	s contains only lowercase English letters.
#

class Solution(object):
    def maxLengthBetweenEqualCharacters(self, s):
        """
        :type s: str
        :rtype: int
        """
        char_index = {}
        max_length = -1
        
        for i, char in enumerate(s):
            if char in char_index:
                length = i - char_index[char] - 1
                max_length = max(max_length, length)
            else:
                char_index[char] = i
                
        return max_length