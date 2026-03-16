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
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def convertToTitle(self, columnNumber):
        """
        :type columnNumber: int
        :rtype: str
        """
        result = ""
        while columnNumber > 0:
            columnNumber -= 1  # Adjust for 1-based indexing
            remainder = columnNumber % 26
            result = chr(remainder + ord('A')) + result
            columnNumber //= 26
        return result