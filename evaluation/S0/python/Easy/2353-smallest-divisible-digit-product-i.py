# Source: https://leetcode.com/problems/smallest-divisible-digit-product-i/   |   Difficulty: Easy
#
# Problem Description:
# You are given two integers n and t. Return the smallest number greater than or equal to n such that the product of its digits is divisible by t.
#
# Example:
# Input: n = 10, t = 2
#
# Output: 10
#
# Explanation:
#
# The digit product of 10 is 0, which is divisible by 2, making it the smallest number greater than or equal to 10 that satisfies the condition.
#
# Constraints:
# 1 <= n <= 100
# 	1 <= t <= 10
#

class Solution(object):
    def smallestNumber(self, n, t):
        """
        :type n: int
        :type t: int
        :rtype: int
        """
        def digit_product(num):
            product = 1
            for digit in str(num):
                product *= int(digit)
            return product

        current = n
        while True:
            if digit_product(current) % t == 0:
                return current
            current += 1