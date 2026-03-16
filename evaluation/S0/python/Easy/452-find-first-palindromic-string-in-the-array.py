# Source: https://leetcode.com/problems/find-first-palindromic-string-in-the-array/   |   Difficulty: Easy
#
# Problem Description:
# Given an array of strings words, return the first palindromic string in the array. If there is no such string, return an empty string "".
#
# A string is palindromic if it reads the same forward and backward.
#
# Example:
# Input: words = ["abc","car","ada","racecar","cool"]
# Output: "ada"
# Explanation: The first string that is palindromic is "ada".
# Note that "racecar" is also palindromic, but it is not the first.
#
# Constraints:
# 1 <= words.length <= 100
# 	1 <= words[i].length <= 100
# 	words[i] consists only of lowercase English letters.
#

class Solution(object):
    def firstPalindrome(self, words):
        """
        :type words: List[str]
        :rtype: str
        """
        for word in words:
            if word == word[::-1]:
                return word
        return ""