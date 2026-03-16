# Source: https://leetcode.com/problems/convert-date-to-binary/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string date representing a Gregorian calendar date in the yyyy-mm-dd format.
#
# date can be written in its binary representation obtained by converting year, month, and day to their binary representations without any leading zeroes and writing them down in year-month-day format.
#
# Return the binary representation of date.
#
# Example:
# Input: date = "2080-02-29"
#
# Output: "100000100000-10-11101"
#
# Explanation:
#
# 100000100000, 10, and 11101 are the binary representations of 2080, 02, and 29 respectively.
#
# Constraints:
# date.length == 10
# 	date[4] == date[7] == '-', and all other date[i]'s are digits.
# 	The input is generated such that date represents a valid Gregorian calendar date between Jan 1st, 1900 and Dec 31st, 2100 (both inclusive).
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
    def convertDateToBinary(self, date):
        """
        :type date: str
        :rtype: str
        """
        year, month, day = date.split('-')
        return f"{bin(int(year))[2:]}-{bin(int(month))[2:]}-{bin(int(day))[2:]}"