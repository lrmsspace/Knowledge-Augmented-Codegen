# Source: https://leetcode.com/problems/check-if-all-characters-have-equal-number-of-occurrences/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s, return true if s is a good string, or false otherwise.
#
# A string s is good if all the characters that appear in s have the same number of occurrences (i.e., the same frequency).
#
# Example:
# Input: s = "abacbc"
# Output: true
# Explanation: The characters that appear in s are 'a', 'b', and 'c'. All characters occur 2 times in s.
#
# Constraints:
# 1 <= s.length <= 1000
# 	s consists of lowercase English letters.
#

class Solution(object):
    def areOccurrencesEqual(self, s):
        """
        :type s: str
        :rtype: bool
        """
        freq = {}
        for char in s:
            freq[char] = freq.get(char, 0) + 1
        
        occurrences = set(freq.values())
        return len(occurrences) == 1