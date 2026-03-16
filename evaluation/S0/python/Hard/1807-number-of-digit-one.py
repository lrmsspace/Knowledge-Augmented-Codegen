# Source: https://leetcode.com/problems/number-of-digit-one/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.
#
# Example:
# Input: n = 13
# Output: 6
#
# Constraints:
# 0 <= n <= 109
#

class Solution(object):
    def countDigitOne(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n <= 0:
            return 0
        
        count = 0
        factor = 1
        
        while factor <= n:
            lower_numbers = n - (n // factor) * factor
            current_digit = (n // factor) % 10
            higher_numbers = n // (factor * 10)
            
            if current_digit == 0:
                count += higher_numbers * factor
            elif current_digit == 1:
                count += higher_numbers * factor + lower_numbers + 1
            else:
                count += (higher_numbers + 1) * factor
            
            factor *= 10
        
        return count