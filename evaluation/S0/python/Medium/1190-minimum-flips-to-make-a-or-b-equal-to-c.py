# Source: https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/   |   Difficulty: Medium
#
# Problem Description:
# Given 3 positives numbers a, b and c. Return the minimum flips required in some bits of a and b to make ( a OR b == c ). (bitwise OR operation).
# Flip operation consists of change any single bit 1 to 0 or change the bit 0 to 1 in their binary representation.
#
# Example:
# Input: a = 2, b = 6, c = 5
# Output: 3
# Explanation: After flips a = 1 , b = 4 , c = 5 such that (a OR b == c)
#
# Constraints:
# 1 <= a <= 10^9
# 	1 <= b <= 10^9
# 	1 <= c <= 10^9
#

class Solution(object):
    def minFlips(self, a, b, c):
        """
        :type a: int
        :type b: int
        :type c: int
        :rtype: int
        """
        flips = 0
        for i in range(32):  # Assuming 32-bit integers
            bit_a = (a >> i) & 1
            bit_b = (b >> i) & 1
            bit_c = (c >> i) & 1
            
            if bit_c == 0:
                flips += bit_a + bit_b  # Both bits need to be flipped to 0
            else:
                if bit_a == 0 and bit_b == 0:
                    flips += 1  # One of the bits needs to be flipped to 1
                    
        return flips