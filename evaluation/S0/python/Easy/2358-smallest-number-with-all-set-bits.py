# Source: https://leetcode.com/problems/smallest-number-with-all-set-bits/   |   Difficulty: Easy
#
# Problem Description:
# You are given a positive number n.
#
# Return the smallest number x greater than or equal to n, such that the binary representation of x contains only set bits
#
# Example:
# Input: n = 5
#
# Output: 7
#
# Explanation:
#
# The binary representation of 7 is "111".
#
# Constraints:
# 1 <= n <= 1000
#

class Solution(object):
    def smallestNumber(self, n):
        """
        :type n: int
        :rtype: int
        """
        length = n.bit_length()
        return (1 << length) - 1