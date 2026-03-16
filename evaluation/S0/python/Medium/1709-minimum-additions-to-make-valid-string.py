# Source: https://leetcode.com/problems/minimum-additions-to-make-valid-string/   |   Difficulty: Medium
#
# Problem Description:
# Given a string word to which you can insert letters "a", "b" or "c" anywhere and any number of times, return the minimum number of letters that must be inserted so that word becomes valid.
#
# A string is called valid if it can be formed by concatenating the string "abc" several times.
#
# Example:
# Input: word = "b"
# Output: 2
# Explanation: Insert the letter "a" right before "b", and the letter "c" right next to "b" to obtain the valid string "abc".
#
# Constraints:
# 1 <= word.length <= 50
# 	word consists of letters "a", "b" and "c" only.
#

class Solution(object):
    def addMinimum(self, word):
        """
        :type word: str
        :rtype: int
        """
        count = 0
        expected_char = 'a'
        
        for char in word:
            while char != expected_char:
                count += 1
                expected_char = chr(((ord(expected_char) - ord('a') + 1) % 3) + ord('a'))
            expected_char = chr(((ord(expected_char) - ord('a') + 1) % 3) + ord('a'))
        
        while expected_char != 'a':
            count += 1
            expected_char = chr(((ord(expected_char) - ord('a') + 1) % 3) + ord('a'))
        
        return count