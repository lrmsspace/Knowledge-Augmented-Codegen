# Source: https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s, return the maximum length of a substring such that it contains at most two occurrences of each character.
#
# Example:
# Input: s = "bcbbbcba"
#
# Output: 4
#
# Explanation:
# The following substring has a length of 4 and contains at most two occurrences of each character: "bcbbbcba".
#
# Constraints:
# 2 <= s.length <= 100
# 	s consists only of lowercase English letters.
#

class Solution(object):
    def maximumLengthSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        left = 0
        char_count = {}
        max_length = 0

        for right in range(len(s)):
            char_count[s[right]] = char_count.get(s[right], 0) + 1

            while any(count > 2 for count in char_count.values()):
                char_count[s[left]] -= 1
                if char_count[s[left]] == 0:
                    del char_count[s[left]]
                left += 1

            max_length = max(max_length, right - left + 1)

        return max_length