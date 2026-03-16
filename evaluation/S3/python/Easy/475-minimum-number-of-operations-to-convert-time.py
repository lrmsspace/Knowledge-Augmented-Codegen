# Source: https://leetcode.com/problems/minimum-number-of-operations-to-convert-time/   |   Difficulty: Easy
#
# Problem Description:
# You are given two strings current and correct representing two 24-hour times.
#
# 24-hour times are formatted as "HH:MM", where HH is between 00 and 23, and MM is between 00 and 59. The earliest 24-hour time is 00:00, and the latest is 23:59.
#
# In one operation you can increase the time current by 1, 5, 15, or 60 minutes. You can perform this operation any number of times.
#
# Return the minimum number of operations needed to convert current to correct.
#
# Example:
# Input: current = "02:30", correct = "04:35"
# Output: 3
# Explanation:
# We can convert current to correct in 3 operations as follows:
# - Add 60 minutes to current. current becomes "03:30".
# - Add 60 minutes to current. current becomes "04:30".
# - Add 5 minutes to current. current becomes "04:35".
# It can be proven that it is not possible to convert current to correct in fewer than 3 operations.
#
# Constraints:
# current and correct are in the format "HH:MM"
# 	current <= correct
#
# Helpful references (internal KB):
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
# - Integration by Simpson's formula (number, interval, enumeration, simulation)
#   • When to use: Use when approximating definite integrals of functions that are sufficiently smooth over a given interval. It is effective for achieving good accuracy with a moderate number of subintervals.
#   • Idea: Simpson's formula approximates a definite integral by dividing the integration interval into an even number of subintervals and approximating the function over each pair of subintervals with a parabola. This method offers a higher order of accuracy compared to simpler rules, typically achieving O(N^4) accuracy for N subintervals.
#   • Invariants: The sum accumulates weighted function values for all processed subintervals.; The subinterval width 'h' remains constant across the entire integration range.
#   • Tips: Ensure the total number of subintervals (2n) is always even for the composite rule.; The weights for function evaluations follow a specific 1-4-2-4-...-2-4-1 pattern.
#   • Pitfalls: Incorrectly applying the weighting coefficients, especially at the boundaries or interior points.; Using an odd number of subintervals, which invalidates the parabolic approximation for the composite rule.
# - Bit manipulation (number, enumeration, simulation)
#   • When to use: When problems involve manipulating individual bits of numbers, representing sets as bitmasks, or optimizing operations on powers of two. It is also useful for certain combinatorics and dynamic programming problems.
#   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators. This technique is often used to optimize computations, manage boolean flags efficiently, or represent subsets, typically achieving O(1) complexity for fixed-size integers.
#   • Invariants: Each bit in the mask accurately reflects the inclusion or exclusion status of its corresponding element.; Bitwise operations maintain the integrity of unaffected bits.
#   • Tips: Use (1 << k) to create a mask with the k-th bit set.; n & (n-1) clears the least significant set bit.
#   • Pitfalls: Incorrect operator precedence can lead to subtle bugs.; Mixing signed and unsigned integers in bitwise operations can yield unexpected results.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def convertTime(self, current, correct):
        """
        :type current: str
        :type correct: str
        :rtype: int
        """
        def time_to_minutes(t):
            h, m = map(int, t.split(':'))
            return h * 60 + m

        current_minutes = time_to_minutes(current)
        correct_minutes = time_to_minutes(correct)
        diff = correct_minutes - current_minutes

        operations = 0
        for increment in [60, 15, 5, 1]:
            operations += diff // increment
            diff %= increment

        return operations