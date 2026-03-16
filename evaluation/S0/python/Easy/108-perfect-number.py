# Source: https://leetcode.com/problems/perfect-number/   |   Difficulty: Easy
#
# Problem Description:
# A perfect number is a positive integer that is equal to the sum of its positive divisors, excluding the number itself. A divisor of an integer x is an integer that can divide x evenly.
#
# Given an integer n, return true if n is a perfect number, otherwise return false.
#
# Example:
# Input: num = 28
# Output: true
# Explanation: 28 = 1 + 2 + 4 + 7 + 14
# 1, 2, 4, 7, and 14 are all divisors of 28.
#
# Constraints:
# 1 <= num <= 108
#

class Solution(object):
    def checkPerfectNumber(self, num):
        """
        :type num: int
        :rtype: bool
        """
        if num < 2:
            return False
        
        divisors_sum = 1  # 1 is a divisor of every number
        for i in range(2, int(num**0.5) + 1):
            if num % i == 0:
                divisors_sum += i
                if i != num // i:
                    divisors_sum += num // i
        
        return divisors_sum == num