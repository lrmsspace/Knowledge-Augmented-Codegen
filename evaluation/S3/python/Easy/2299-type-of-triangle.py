# Source: https://leetcode.com/problems/type-of-triangle/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed integer array nums of size 3 which can form the sides of a triangle.
#
#
# 	A triangle is called equilateral if it has all sides of equal length.
# 	A triangle is called isosceles if it has exactly two sides of equal length.
# 	A triangle is called scalene if all its sides are of different lengths.
#
#
# Return a string representing the type of triangle that can be formed or "none" if it cannot form a triangle.
#
# Example:
# Input: nums = [3,3,3]
# Output: "equilateral"
# Explanation: Since all the sides are of equal length, therefore, it will form an equilateral triangle.
#
# Constraints:
# nums.length == 3
# 	1 <= nums[i] <= 100
#
# Helpful references (internal KB):
# - Oriented area of a triangle (geometry, number, simulation)
#   • When to use: Use when determining the orientation of three 2D points (clockwise, counterclockwise, or collinear) or calculating the signed area of a triangle formed by them. It's crucial for geometric algorithms like convex hull construction and point-in-polygon tests.
#   • Idea: Calculates the signed area of a triangle defined by three 2D points, indicating their orientation relative to each other. A positive sign typically means counterclockwise, negative means clockwise, and zero indicates collinearity.
#   • Invariants: The sign of the result correctly indicates the orientation of p1, p2, p3 (e.g., positive for counter-clockwise).; If the points are collinear, the calculated oriented area is exactly zero.
#   • Tips: The sign of the result directly indicates the orientation of the points.; The absolute value of the result gives the standard unsigned area of the triangle.
#   • Pitfalls: Floating-point precision issues can lead to incorrect collinearity checks or orientation.; Inconsistent definitions of 'clockwise' vs. 'counterclockwise' can flip the sign interpretation.
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def triangleType(self, nums):
        """
        :type nums: List[int]
        :rtype: str
        """
        nums.sort()
        if nums[0] + nums[1] <= nums[2]:
            return "none"
        elif nums[0] == nums[1] == nums[2]:
            return "equilateral"
        elif nums[0] == nums[1] or nums[1] == nums[2]:
            return "isosceles"
        else:
            return "scalene"