# Source: https://leetcode.com/problems/reverse-bits/   |   Difficulty: Easy
#
# Problem Description:
# Reverse bits of a given 32 bits signed integer.
#
# Example:
# Input: n = 43261596
#
# Output: 964176192
#
# Explanation:
#
#
# 	
# 		
# 			Integer
# 			Binary
# 		
# 		
# 			43261596
# 			00000010100101000001111010011100
# 		
# 		
# 			964176192
# 			00111001011110000010100101000000
#
# Constraints:
# 0 <= n <= 231 - 2
# 	n is even.
#
#
#  
# Follow up: If this function is called many times, how would you optimize it?
#

class Solution(object):
    def reverseBits(self, n):
        """
        :type n: int
        :rtype: int
        """
        result = 0
        for i in range(32):
            result <<= 1
            result |= n & 1
            n >>= 1
        return result