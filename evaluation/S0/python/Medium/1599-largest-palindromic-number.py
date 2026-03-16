# Source: https://leetcode.com/problems/largest-palindromic-number/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string num consisting of digits only.
#
# Return the largest palindromic integer (in the form of a string) that can be formed using digits taken from num. It should not contain leading zeroes.
#
# Example:
# Input: num = "444947137"
# Output: "7449447"
# Explanation: 
# Use the digits "4449477" from "444947137" to form the palindromic integer "7449447".
# It can be shown that "7449447" is the largest palindromic integer that can be formed.
#
# Constraints:
# 1 <= num.length <= 105
# 	num consists of digits.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def largestPalindromic(self, num):
        """
        :type num: str
        :rtype: str
        """
        from collections import Counter

        count = Counter(num)
        left_half = []
        middle_digit = ''

        for digit in sorted(count.keys(), reverse=True):
            pairs = count[digit] // 2
            left_half.append(digit * pairs)
            if count[digit] % 2 == 1 and (middle_digit == '' or digit > middle_digit):
                middle_digit = digit

        left_half_str = ''.join(left_half).lstrip('0')
        if left_half_str == '':
            if middle_digit:
                return middle_digit
            else:
                return '0'

        right_half_str = left_half_str[::-1]
        return left_half_str + middle_digit + right_half_str