# Source: https://leetcode.com/problems/determine-if-two-events-have-conflict/   |   Difficulty: Easy
#
# Problem Description:
# You are given two arrays of strings that represent two inclusive events that happened on the same day, event1 and event2, where:
#
#
# 	event1 = [startTime1, endTime1] and
# 	event2 = [startTime2, endTime2].
#
#
# Event times are valid 24 hours format in the form of HH:MM.
#
# A conflict happens when two events have some non-empty intersection (i.e., some moment is common to both events).
#
# Return true if there is a conflict between two events. Otherwise, return false.
#
# Example:
# Input: event1 = ["01:15","02:00"], event2 = ["02:00","03:00"]
# Output: true
# Explanation: The two events intersect at time 2:00.
#
# Constraints:
# event1.length == event2.length == 2
# 	event1[i].length == event2[i].length == 5
# 	startTime1 <= endTime1
# 	startTime2 <= endTime2
# 	All the event times follow the HH:MM format.
#
# Helpful references (internal KB):
# - Integration by Simpson's formula (number, interval, enumeration, simulation)
#   • When to use: Use when approximating definite integrals of functions that are sufficiently smooth over a given interval. It is effective for achieving good accuracy with a moderate number of subintervals.
#   • Idea: Simpson's formula approximates a definite integral by dividing the integration interval into an even number of subintervals and approximating the function over each pair of subintervals with a parabola. This method offers a higher order of accuracy compared to simpler rules, typically achieving O(N^4) accuracy for N subintervals.
#   • Invariants: The sum accumulates weighted function values for all processed subintervals.; The subinterval width 'h' remains constant across the entire integration range.
#   • Tips: Ensure the total number of subintervals (2n) is always even for the composite rule.; The weights for function evaluations follow a specific 1-4-2-4-...-2-4-1 pattern.
#   • Pitfalls: Incorrectly applying the weighting coefficients, especially at the boundaries or interior points.; Using an odd number of subintervals, which invalidates the parabolic approximation for the composite rule.
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def haveConflict(self, event1, event2):
        """
        :type event1: List[str]
        :type event2: List[str]
        :rtype: bool
        """
        # Convert time from "HH:MM" to minutes since midnight
        def time_to_minutes(t):
            h, m = map(int, t.split(':'))
            return h * 60 + m
        
        start1, end1 = map(time_to_minutes, event1)
        start2, end2 = map(time_to_minutes, event2)
        
        # Check for conflict: events overlap if one starts before the other ends
        return not (end1 <= start2 or end2 <= start1)