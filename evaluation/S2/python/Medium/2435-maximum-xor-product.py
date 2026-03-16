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
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumXorProduct(self, a, b, n):
        """
        :type a: int
        :type b: int
        :type n: int
        :rtype: int
        """
        max_xor = 0
        for i in range(n):
            max_xor |= (1 << i)  # This will create a number with n bits set to 1
        
        # The best x to maximize (a XOR x) * (b XOR x) is to choose x such that it flips the bits of a and b where they differ.
        # This can be achieved by XORing a and b with max_xor, which will flip all bits up to n.
        x = (a ^ b) & max_xor
        
        return ((a ^ x) * (b ^ x)) % (10**9 + 7)