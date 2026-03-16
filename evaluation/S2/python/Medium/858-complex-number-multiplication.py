# Source: https://leetcode.com/problems/complex-number-multiplication/   |   Difficulty: Medium
#
# Problem Description:
# A complex number can be represented as a string on the form "real+imaginaryi" where:
#
#
# 	real is the real part and is an integer in the range [-100, 100].
# 	imaginary is the imaginary part and is an integer in the range [-100, 100].
# 	i2 == -1.
#
#
# Given two complex numbers num1 and num2 as strings, return a string of the complex number that represents their multiplications.
#
# Example:
# Input: num1 = "1+1i", num2 = "1+1i"
# Output: "0+2i"
# Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.
#
# Constraints:
# num1 and num2 are valid complex numbers.
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
    def complexNumberMultiply(self, num1, num2):
        """
        :type num1: str
        :type num2: str
        :rtype: str
        """
        def parse_complex(num):
            real, imag = num.split('+')
            return int(real), int(imag[:-1])  # Remove the trailing 'i'

        a, b = parse_complex(num1)
        c, d = parse_complex(num2)

        real_part = a * c - b * d
        imag_part = a * d + b * c

        return f"{real_part}+{imag_part}i"