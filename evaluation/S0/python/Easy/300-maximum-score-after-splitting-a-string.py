# Source: https://leetcode.com/problems/maximum-score-after-splitting-a-string/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s of zeros and ones, return the maximum score after splitting the string into two non-empty substrings (i.e. left substring and right substring).
#
# The score after splitting a string is the number of zeros in the left substring plus the number of ones in the right substring.
#
# Example:
# Input: s = "011101"
# Output: 5 
# Explanation: 
# All possible ways of splitting s into two non-empty substrings are:
# left = "0" and right = "11101", score = 1 + 4 = 5 
# left = "01" and right = "1101", score = 1 + 3 = 4 
# left = "011" and right = "101", score = 1 + 2 = 3 
# left = "0111" and right = "01", score = 1 + 1 = 2 
# left = "01110" and right = "1", score = 2 + 1 = 3
#
# Constraints:
# 2 <= s.length <= 500
# 	The string s consists of characters '0' and '1' only.
#

class Solution(object):
    def maxScore(self, s):
        """
        :type s: str
        :rtype: int
        """
        max_score = 0
        n = len(s)
        
        for i in range(1, n):
            left = s[:i]
            right = s[i:]
            score = left.count('0') + right.count('1')
            max_score = max(max_score, score)
        
        return max_score