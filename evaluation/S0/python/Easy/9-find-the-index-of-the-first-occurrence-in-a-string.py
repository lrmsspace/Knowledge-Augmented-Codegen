# Source: https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/   |   Difficulty: Easy
#
# Problem Description:
# Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
#
# Example:
# Input: haystack = "sadbutsad", needle = "sad"
# Output: 0
# Explanation: "sad" occurs at index 0 and 6.
# The first occurrence is at index 0, so we return 0.
#
# Constraints:
# 1 <= haystack.length, needle.length <= 104
# 	haystack and needle consist of only lowercase English characters.
#

class Solution(object):
    def strStr(self, haystack, needle):
        """
        :type haystack: str
        :type needle: str
        :rtype: int
        """
        n = len(needle)
        for i in range(len(haystack) - n + 1):
            if haystack[i:i+n] == needle:
                return i
        return -1