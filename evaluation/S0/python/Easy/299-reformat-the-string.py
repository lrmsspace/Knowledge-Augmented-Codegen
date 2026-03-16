# Source: https://leetcode.com/problems/reformat-the-string/   |   Difficulty: Easy
#
# Problem Description:
# You are given an alphanumeric string s. (Alphanumeric string is a string consisting of lowercase English letters and digits).
#
# You have to find a permutation of the string where no letter is followed by another letter and no digit is followed by another digit. That is, no two adjacent characters have the same type.
#
# Return the reformatted string or return an empty string if it is impossible to reformat the string.
#
# Example:
# Input: s = "a0b1c2"
# Output: "0a1b2c"
# Explanation: No two adjacent characters have the same type in "0a1b2c". "a0b1c2", "0a1b2c", "0c2a1b" are also valid permutations.
#
# Constraints:
# 1 <= s.length <= 500
# 	s consists of only lowercase English letters and/or digits.
#

class Solution(object):
    def reformat(self, s):
        """
        :type s: str
        :rtype: str
        """
        letters = []
        digits = []
        
        for char in s:
            if char.isalpha():
                letters.append(char)
            elif char.isdigit():
                digits.append(char)
        
        if abs(len(letters) - len(digits)) > 1:
            return ""
        
        reformatted = []
        if len(letters) >= len(digits):
            longer, shorter = letters, digits
        else:
            longer, shorter = digits, letters
        
        for i in range(len(shorter)):
            reformatted.append(longer[i])
            reformatted.append(shorter[i])
        
        if len(longer) > len(shorter):
            reformatted.append(longer[-1])
        
        return "".join(reformatted)