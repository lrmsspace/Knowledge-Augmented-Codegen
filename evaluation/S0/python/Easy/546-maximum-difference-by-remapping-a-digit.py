# Source: https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer num. You know that Bob will sneakily remap one of the 10 possible digits (0 to 9) to another digit.
#
# Return the difference between the maximum and minimum values Bob can make by remapping exactly one digit in num.
#
# 	The resulting number after remapping can contain leading zeroes.
#
# Example:
# Input: num = 11891
# Output: 99009
# Explanation: 
# To achieve the maximum value, Bob can remap the digit 1 to the digit 9 to yield 99899.
# To achieve the minimum value, Bob can remap the digit 1 to the digit 0, yielding 890.
# The difference between these two numbers is 99009.
#
# Constraints:
# 1 <= num <= 108
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minMaxDifference(self, num):
        """
        :type num: int
        :rtype: int
        """
        num_str = str(num)
        
        # Find max value
        for digit in num_str:
            if digit != '9':
                max_digit = digit
                break
        else:
            max_digit = None  # All digits are 9
        
        if max_digit is not None:
            max_value = int(num_str.replace(max_digit, '9'))
        else:
            max_value = num
        
        # Find min value
        first_digit = num_str[0]
        if first_digit != '1':
            min_digit = first_digit
            min_value = int(num_str.replace(min_digit, '1'))
        else:
            for digit in num_str[1:]:
                if digit != '0' and digit != '1':
                    min_digit = digit
                    break
            else:
                min_digit = None  # All digits are 0 or 1
            
            if min_digit is not None:
                min_value = int(num_str.replace(min_digit, '0'))
            else:
                min_value = num
        
        return max_value - min_value