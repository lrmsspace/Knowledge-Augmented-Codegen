# Source: https://leetcode.com/problems/complement-of-base-10-integer/   |   Difficulty: Easy
#
# Problem Description:
# The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's to 0's in its binary representation.
#
#
# 	For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
#
#
# Given an integer n, return its complement.
#
# Example:
# Input: n = 5
# Output: 2
# Explanation: 5 is "101" in binary, with complement "010" in binary, which is 2 in base-10.
#
# Constraints:
# 0 <= n < 109
#
#
#  
# Note: This question is the same as 476: https://leetcode.com/problems/number-complement/
#

class Solution(object):
    def bitwiseComplement(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 0:
            return 1
        
        bit_length = n.bit_length()
        all_ones = (1 << bit_length) - 1
        complement = n ^ all_ones
        
        return complement