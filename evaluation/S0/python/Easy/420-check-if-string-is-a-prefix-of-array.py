# Source: https://leetcode.com/problems/check-if-string-is-a-prefix-of-array/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s and an array of strings words, determine whether s is a prefix string of words.
#
# A string s is a prefix string of words if s can be made by concatenating the first k strings in words for some positive k no larger than words.length.
#
# Return true if s is a prefix string of words, or false otherwise.
#
# Example:
# Input: s = "iloveleetcode", words = ["i","love","leetcode","apples"]
# Output: true
# Explanation:
# s can be made by concatenating "i", "love", and "leetcode" together.
#
# Constraints:
# 1 <= words.length <= 100
# 	1 <= words[i].length <= 20
# 	1 <= s.length <= 1000
# 	words[i] and s consist of only lowercase English letters.
#

class Solution(object):
    def isPrefixString(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: bool
        """
        prefix = ""
        for word in words:
            prefix += word
            if prefix == s:
                return True
            if len(prefix) > len(s):
                return False
        return False