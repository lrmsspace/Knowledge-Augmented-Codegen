# Source: https://leetcode.com/problems/count-numbers-with-unique-digits/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return the count of all numbers with unique digits, x, where 0 <= x < 10n.
#
# Example:
# Input: n = 2
# Output: 91
# Explanation: The answer should be the total numbers in the range of 0 ≤ x < 100, excluding 11,22,33,44,55,66,77,88,99
#
# Constraints:
# 0 <= n <= 8
#

class Solution(object):
    def countNumbersWithUniqueDigits(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 0:
            return 1
        if n == 1:
            return 10
        
        count = 10
        unique_digits = 9
        available_number = 9
        
        for i in range(2, n + 1):
            unique_digits *= available_number
            count += unique_digits
            available_number -= 1
            
        return count