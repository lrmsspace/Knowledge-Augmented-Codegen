# Source: https://leetcode.com/problems/fraction-addition-and-subtraction/   |   Difficulty: Medium
#
# Problem Description:
# Given a string expression representing an expression of fraction addition and subtraction, return the calculation result in string format.
#
# The final result should be an irreducible fraction. If your final result is an integer, change it to the format of a fraction that has a denominator 1. So in this case, 2 should be converted to 2/1.
#
# Example:
# Input: expression = "-1/2+1/2"
# Output: "0/1"
#
# Constraints:
# The input string only contains '0' to '9', '/', '+' and '-'. So does the output.
# 	Each fraction (input and output) has the format ±numerator/denominator. If the first input fraction or the output is positive, then '+' will be omitted.
# 	The input only contains valid irreducible fractions, where the numerator and denominator of each fraction will always be in the range [1, 10]. If the denominator is 1, it means this fraction is actually an integer in a fraction format defined above.
# 	The number of given fractions will be in the range [1, 10].
# 	The numerator and denominator of the final result are guaranteed to be valid and in the range of 32-bit int.
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
    def fractionAddition(self, expression):
        """
        :type expression: str
        :rtype: str
        """
        from fractions import Fraction

        # Split the expression into parts
        parts = expression.replace('-', '+-').split('+')
        result = Fraction(0)

        for part in parts:
            if part:  # Skip empty strings
                result += Fraction(part)

        return f"{result.numerator}/{result.denominator}"