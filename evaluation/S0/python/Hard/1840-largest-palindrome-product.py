# Source: https://leetcode.com/problems/largest-palindrome-product/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer n, return the largest palindromic integer that can be represented as the product of two n-digits integers. Since the answer can be very large, return it modulo 1337.
#
# Example:
# Input: n = 2
# Output: 987
# Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
#
# Constraints:
# 1 <= n <= 8
#

class Solution(object):
    def largestPalindrome(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 1:
            return 9
        upper = 10**n - 1
        lower = 10**(n-1)
        max_num = upper * upper

        for first_half in range(max_num // 10, lower - 1, -1):
            palin_str = str(first_half) + str(first_half)[::-1]
            palin_num = int(palin_str)

            for i in range(upper, lower - 1, -1):
                if palin_num // i > upper:
                    break
                if palin_num % i == 0:
                    return palin_num % 1337

        return None