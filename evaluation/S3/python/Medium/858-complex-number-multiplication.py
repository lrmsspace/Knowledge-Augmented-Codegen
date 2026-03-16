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
# - Expression parsing (stack, simulation)
#   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
#   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
#   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
#   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
#   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
# - Finding common tangents to two circles (geometry, number, enumeration, simulation)
#   • When to use: When needing to find lines that are tangent to two given circles simultaneously. This method is suitable for problems requiring precise geometric line calculations.
#   • Idea: This algorithm finds common tangent lines to two circles by formulating the problem as a system of algebraic equations based on distance constraints. It involves solving a quadratic equation for line coefficients, typically resulting in constant time complexity after initial setup.
#   • Invariants: The distance from the line ax + by + c = 0 to the first circle's center is r1.; The distance from the line ax + by + c = 0 to the second circle's center is r2.
#   • Tips: Normalize the line equation (a^2 + b^2 = 1) to ensure unique representations.; Shift one circle to the origin for simpler calculations, then shift the resulting lines back.
#   • Pitfalls: Forgetting to normalize the line equation can lead to non-unique solutions.; Incorrectly handling the modulus signs (±r1, ±r2) can miss valid tangents.
# - Check if two segments intersect (geometry, number, simulation)
#   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
#   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
#   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
#   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
#   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
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
        def parse_complex_number(s):
            real, imag = s.split('+')
            imag = imag[:-1]  # Remove the trailing 'i'
            return int(real), int(imag)

        a, b = parse_complex_number(num1)
        c, d = parse_complex_number(num2)

        real_part = a * c - b * d
        imag_part = a * d + b * c

        return f"{real_part}+{imag_part}i"