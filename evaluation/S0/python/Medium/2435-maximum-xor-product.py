# Source: https://leetcode.com/problems/maximum-xor-product/   |   Difficulty: Medium
#
# Problem Description:
# Given three integers a, b, and n, return the maximum value of (a XOR x) * (b XOR x) where 0 <= x < 2n.
#
# Since the answer may be too large, return it modulo 109 + 7.
#
# Note that XOR is the bitwise XOR operation.
#
# Example:
# Input: a = 12, b = 5, n = 4
# Output: 98
# Explanation: For x = 2, (a XOR x) = 14 and (b XOR x) = 7. Hence, (a XOR x) * (b XOR x) = 98. 
# It can be shown that 98 is the maximum value of (a XOR x) * (b XOR x) for all 0 <= x < 2n.
#
# Constraints:
# 0 <= a, b < 250
# 	0 <= n <= 50
#

class Solution(object):
    def maximumXorProduct(self, a, b, n):
        """
        :type a: int
        :type b: int
        :type n: int
        :rtype: int
        """
        MOD = 10**9 + 7
        max_x = (1 << n) - 1  # 最大的 x 值为 2^n - 1
        max_product = 0

        for x in range(max_x + 1):
            product = (a ^ x) * (b ^ x)
            max_product = max(max_product, product)

        return max_product % MOD