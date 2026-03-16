# Source: https://leetcode.com/problems/longest-palindrome/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s which consists of lowercase or uppercase letters, return the length of the longest palindrome that can be built with those letters.
#
# Letters are case sensitive, for example, "Aa" is not considered a palindrome.
#
# Example:
# Input: s = "abccccdd"
# Output: 7
# Explanation: One longest palindrome that can be built is "dccaccd", whose length is 7.
#
# Constraints:
# 1 <= s.length <= 2000
# 	s consists of lowercase and/or uppercase English letters only.
#

class Solution(object):
    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: int
        """
        char_count = {}
        for char in s:
            char_count[char] = char_count.get(char, 0) + 1

        length = 0
        odd_found = False

        for count in char_count.values():
            if count % 2 == 0:
                length += count
            else:
                length += count - 1
                odd_found = True

        if odd_found:
            length += 1

        return length