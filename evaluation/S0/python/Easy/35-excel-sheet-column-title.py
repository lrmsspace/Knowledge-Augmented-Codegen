# Source: https://leetcode.com/problems/excel-sheet-column-title/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.
#
# For example:
#
#
# A -> 1
# B -> 2
# C -> 3
# ...
# Z -> 26
# AA -> 27
# AB -> 28 
# ...
#
# Example:
# Input: columnNumber = 1
# Output: "A"
#
# Constraints:
# 1 <= columnNumber <= 231 - 1
#

class Solution(object):
    def convertToTitle(self, columnNumber):
        """
        :type columnNumber: int
        :rtype: str
        """
        result = []
        while columnNumber > 0:
            columnNumber -= 1  # Adjust for 0-based indexing
            remainder = columnNumber % 26
            result.append(chr(remainder + ord('A')))
            columnNumber //= 26
        result.reverse()
        return ''.join(result)