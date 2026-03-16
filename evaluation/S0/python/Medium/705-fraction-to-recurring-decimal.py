# Source: https://leetcode.com/problems/fraction-to-recurring-decimal/   |   Difficulty: Medium
#
# Problem Description:
# Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
#
# If the fractional part is repeating, enclose the repeating part in parentheses
#
# If multiple answers are possible, return any of them.
#
# It is guaranteed that the length of the answer string is less than 104 for all the given inputs.
#
# Note that if the fraction can be represented as a finite length string, you must return it.
#
# Example:
# Input: numerator = 1, denominator = 2
# Output: "0.5"
#
# Constraints:
# -231 <= numerator, denominator <= 231 - 1
# 	denominator != 0
#

class Solution(object):
    def fractionToDecimal(self, numerator, denominator):
        """
        :type numerator: int
        :type denominator: int
        :rtype: str
        """
        if numerator == 0:
            return "0"
        
        res = []
        
        # Determine the sign
        if (numerator < 0) ^ (denominator < 0):
            res.append("-")
        
        # Work with absolute values
        num, den = abs(numerator), abs(denominator)
        
        # Integer part
        res.append(str(num // den))
        remainder = num % den
        
        if remainder == 0:
            return "".join(res)
        
        res.append(".")
        
        # Fractional part
        rem_map = {}
        idx = len(res)
        
        while remainder != 0:
            if remainder in rem_map:
                insert_idx = rem_map[remainder]
                res.insert(insert_idx, "(")
                res.append(")")
                break
            
            rem_map[remainder] = idx
            remainder *= 10
            res.append(str(remainder // den))
            remainder %= den
            idx += 1
        
        return "".join(res)