# Source: https://leetcode.com/problems/number-of-1-bits/   |   Difficulty: Easy
#
# Problem Description:
# Given a positive integer n, write a function that returns the number of set bits in its binary representation (also known as the Hamming weight).
#
# Example:
# Input: n = 11
#
# Output: 3
#
# Explanation:
#
# The input binary string 1011 has a total of three set bits.
#
# Constraints:
# 1 <= n <= 231 - 1
#
#
#  
# Follow up: If this function is called many times, how would you optimize it?
#

class Solution(object):
    def hammingWeight(self, n):
        """
        :type n: int
        :rtype: int
        """
        count = 0
        while n:
            count += n & 1
            n >>= 1
        return count