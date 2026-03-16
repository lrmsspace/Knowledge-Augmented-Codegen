# Source: https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return the decimal value of the binary string formed by concatenating the binary representations of 1 to n in order, modulo 109 + 7.
#
# Example:
# Input: n = 1
# Output: 1
# Explanation: "1" in binary corresponds to the decimal value 1.
#
# Constraints:
# 1 <= n <= 105
#

class Solution(object):
    def concatenatedBinary(self, n):
        """
        :type n: int
        :rtype: int
        """
        MOD = 10**9 + 7
        result = 0
        length = 0
        
        for i in range(1, n + 1):
            if (i & (i - 1)) == 0:  # Check if i is a power of 2
                length += 1
            result = ((result << length) | i) % MOD
        
        return result