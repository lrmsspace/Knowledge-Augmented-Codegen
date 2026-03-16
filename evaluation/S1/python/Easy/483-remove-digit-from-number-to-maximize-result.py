# Source: https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string number representing a positive integer and a character digit.
#
# Return the resulting string after removing exactly one occurrence of digit from number such that the value of the resulting string in decimal form is maximized. The test cases are generated such that digit occurs at least once in number.
#
# Example:
# Input: number = "123", digit = "3"
# Output: "12"
# Explanation: There is only one '3' in "123". After removing '3', the result is "12".
#
# Constraints:
# 2 <= number.length <= 100
# 	number consists of digits from '1' to '9'.
# 	digit is a digit from '1' to '9'.
# 	digit occurs at least once in number.
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
    def removeDigit(self, number, digit):
        """
        :type number: str
        :type digit: str
        :rtype: str
        """
        max_number = ""
        for i in range(len(number)):
            if number[i] == digit:
                candidate = number[:i] + number[i+1:]
                if candidate > max_number:
                    max_number = candidate
        return max_number