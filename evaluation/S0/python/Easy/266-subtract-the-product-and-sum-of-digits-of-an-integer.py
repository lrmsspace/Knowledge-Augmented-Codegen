# Source: https://leetcode.com/problems/subtract-the-product-and-sum-of-digits-of-an-integer/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer number n, return the difference between the product of its digits and the sum of its digits.
#
# Example:
# Input: n = 234
# Output: 15 
# Explanation: 
# Product of digits = 2 * 3 * 4 = 24 
# Sum of digits = 2 + 3 + 4 = 9 
# Result = 24 - 9 = 15
#
# Constraints:
# 1 <= n <= 10^5
#

class Solution(object):
    def subtractProductAndSum(self, n):
        """
        :type n: int
        :rtype: int
        """
        product = 1
        summation = 0
        
        for digit in str(n):
            digit = int(digit)
            product *= digit
            summation += digit
            
        return product - summation