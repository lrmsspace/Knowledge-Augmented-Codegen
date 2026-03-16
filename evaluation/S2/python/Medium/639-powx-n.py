# Source: https://leetcode.com/problems/powx-n/   |   Difficulty: Medium
#
# Problem Description:
# Implement pow(x, n), which calculates x raised to the power n (i.e., xn).
#
# Example:
# Input: x = 2.00000, n = 10
# Output: 1024.00000
#
# Constraints:
# -100.0 < x < 100.0
# 	-231 <= n <= 231-1
# 	n is an integer.
# 	Either x is not zero or n > 0.
# 	-104 <= xn <= 104
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
    def myPow(self, x, n):
        """
        :type x: float
        :type n: int
        :rtype: float
        """
        if n == 0:
            return 1.0
        elif n < 0:
            x = 1 / x
            n = -n
        
        result = 1.0
        current_product = x
        
        while n > 0:
            if n % 2 == 1:  # If n is odd
                result *= current_product
            current_product *= current_product  # Square the base
            n //= 2  # Divide n by 2
        
        return result