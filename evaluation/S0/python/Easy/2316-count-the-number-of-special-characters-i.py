# Source: https://leetcode.com/problems/count-the-number-of-special-characters-i/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string word. A letter is called special if it appears both in lowercase and uppercase in word.
#
# Return the number of special letters in word.
#
# Example:
# Input: word = "aaAbcBC"
#
# Output: 3
#
# Explanation:
#
# The special characters in word are 'a', 'b', and 'c'.
#
# Constraints:
# 1 <= word.length <= 50
# 	word consists of only lowercase and uppercase English letters.
#

class Solution(object):
    def numberOfSpecialChars(self, word):
        """
        :type word: str
        :rtype: int
        """
        lower_set = set()
        upper_set = set()
        
        for char in word:
            if char.islower():
                lower_set.add(char)
            elif char.isupper():
                upper_set.add(char.lower())
        
        special_chars = lower_set.intersection(upper_set)
        return len(special_chars)