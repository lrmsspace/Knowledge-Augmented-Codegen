# Source: https://leetcode.com/problems/longest-substring-without-repeating-characters/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, find the length of the longest substring without duplicate characters.
#
# Example:
# Input: s = "abcabcbb"
# Output: 3
# Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.
#
# Constraints:
# 0 <= s.length <= 5 * 104
# 	s consists of English letters, digits, symbols and spaces.
#

class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        char_index_map = {}
        left = 0
        max_length = 0

        for right in range(len(s)):
            if s[right] in char_index_map and char_index_map[s[right]] >= left:
                left = char_index_map[s[right]] + 1
            char_index_map[s[right]] = right
            max_length = max(max_length, right - left + 1)

        return max_length