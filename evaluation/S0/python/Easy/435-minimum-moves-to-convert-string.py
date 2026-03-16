# Source: https://leetcode.com/problems/minimum-moves-to-convert-string/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s consisting of n characters which are either 'X' or 'O'.
#
# A move is defined as selecting three consecutive characters of s and converting them to 'O'. Note that if a move is applied to the character 'O', it will stay the same.
#
# Return the minimum number of moves required so that all the characters of s are converted to 'O'.
#
# Example:
# Input: s = "XXX"
# Output: 1
# Explanation: XXX -> OOO
# We select all the 3 characters and convert them in one move.
#
# Constraints:
# 3 <= s.length <= 1000
# 	s[i] is either 'X' or 'O'.
#

class Solution(object):
    def minimumMoves(self, s):
        """
        :type s: str
        :rtype: int
        """
        moves = 0
        i = 0
        n = len(s)
        
        while i < n:
            if s[i] == 'X':
                moves += 1
                i += 3  # Skip the next two characters as they are converted to 'O'
            else:
                i += 1  # Move to the next character
        
        return moves