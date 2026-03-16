# Source: https://leetcode.com/problems/reverse-integer/   |   Difficulty: Medium
#
# Problem Description:
# Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.
#
# Assume the environment does not allow you to store 64-bit integers (signed or unsigned).
#
# Example:
# Input: x = 123
# Output: 321
#
# Constraints:
# -231 <= x <= 231 - 1
#
# Helpful references (internal KB):
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
# - Gray code (number, simulation)
#   • When to use: Use when generating a sequence of numbers where adjacent values must differ by only one bit, or for error detection in digital systems. It is also useful for certain combinatorial problems.
#   • Idea: Gray code is a binary numeral system where two successive values differ in exactly one bit position. It can be generated efficiently using bitwise operations in O(1) time per code, or O(N) for N codes.
#   • Invariants: The number of bits in the generated Gray code G(n) is equal to the number of bits in the input binary n.; G(0) is always 0, and G(1) is always 1.
#   • Tips: The most common formula for converting binary n to Gray code G(n) is G(n) = n ^ (n >> 1).; To convert Gray code G(n) back to binary n, use a series of XOR operations: n = G(n) ^ (G(n) >> 1) ^ (G(n) >> 2) ^ ... until zero.
#   • Pitfalls: Confusing Gray code with standard binary representation, which can have multiple bit changes between successive numbers.; Incorrectly implementing the conversion formulas, especially the Gray to binary conversion.
# - Bit manipulation (number, simulation)
#   • When to use: Use when operations on individual bits of an integer are required, for optimizing arithmetic with powers of two, or for efficient management of boolean flags.
#   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators and shifts. These operations typically have O(1) time complexity as they are hardware-level instructions.
#   • Invariants: The total number of bits representing the integer remains constant for fixed-width types.; Applying `n & (1 << k)` isolates the k-th bit, setting all other bits to zero.
#   • Tips: Use `&` with `(1 << k)` to check if the k-th bit is set.; Use `|` with `(1 << k)` to set the k-th bit.
#   • Pitfalls: Be aware of integer overflow when performing large left shifts.; Understand the difference between arithmetic and logical right shifts, especially for signed numbers.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """
        sign = -1 if x < 0 else 1
        x_abs = abs(x)
        reversed_x = 0

        while x_abs != 0:
            digit = x_abs % 10
            reversed_x = reversed_x * 10 + digit
            x_abs //= 10

        reversed_x *= sign

        # Check for overflow
        if reversed_x < -2**31 or reversed_x > 2**31 - 1:
            return 0

        return reversed_x