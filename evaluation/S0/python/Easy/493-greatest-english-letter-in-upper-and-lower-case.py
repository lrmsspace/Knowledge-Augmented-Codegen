# Source: https://leetcode.com/problems/greatest-english-letter-in-upper-and-lower-case/   |   Difficulty: Easy
#
# Problem Description:
# Given a string of English letters s, return the greatest English letter which occurs as both a lowercase and uppercase letter in s. The returned letter should be in uppercase. If no such letter exists, return an empty string.
#
# An English letter b is greater than another letter a if b appears after a in the English alphabet.
#
# Example:
# Input: s = "lEeTcOdE"
# Output: "E"
# Explanation:
# The letter 'E' is the only letter to appear in both lower and upper case.
#
# Constraints:
# 1 <= s.length <= 1000
# 	s consists of lowercase and uppercase English letters.
#

class Solution(object):
    def greatestLetter(self, s):
        """
        :type s: str
        :rtype: str
        """
        lower_set = set()
        upper_set = set()
        
        for char in s:
            if char.islower():
                lower_set.add(char)
            elif char.isupper():
                upper_set.add(char)
        
        greatest_letter = ''
        
        for char in upper_set:
            if char.lower() in lower_set:
                if greatest_letter == '' or char > greatest_letter:
                    greatest_letter = char
        
        return greatest_letter