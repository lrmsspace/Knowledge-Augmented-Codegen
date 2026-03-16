# Source: https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/   |   Difficulty: Hard
#
# Problem Description:
# Alice is throwing n darts on a very large wall. You are given an array darts where darts[i] = [xi, yi] is the position of the ith dart that Alice threw on the wall.
#
# Bob knows the positions of the n darts on the wall. He wants to place a dartboard of radius r on the wall so that the maximum number of darts that Alice throws lie on the dartboard.
#
# Given the integer r, return the maximum number of darts that can lie on the dartboard.
#
# Example:
# Input: darts = [[-2,0],[2,0],[0,2],[0,-2]], r = 2
# Output: 4
# Explanation: Circle dartboard with center in (0,0) and radius = 2 contain all points.
#
# Constraints:
# 1 <= darts.length <= 100
# 	darts[i].length == 2
# 	-104 <= xi, yi <= 104
# 	All the darts are unique
# 	1 <= r <= 5000
#
# Helpful references (internal KB):
# - Search for a pair of intersecting segments (tree, geometry, sweep-line, counting)
#   • When to use: Use this algorithm to efficiently determine if any pair of line segments in a given set intersect. It is particularly effective for detecting geometric overlaps in a 2D plane.
#   • Idea: This algorithm processes segments by sweeping a vertical line across the plane, maintaining an ordered set of active segments to efficiently check for intersections with neighbors. It achieves an optimal time complexity of O(N log N).
#   • Invariants: The sweep line always moves from left to right, processing events in increasing x-coordinate order.; The set of active segments contains all segments currently intersected by the sweep line, ordered by their y-coordinate at the sweep line's current x-position.
#   • Tips: Process events at the same x-coordinate by adding segments before removing them to catch vertex intersections.; Use a balanced binary search tree (e.g., `std::set`) to maintain active segments, ordered by their y-coordinate.
#   • Pitfalls: Incorrect event ordering (e.g., removing before adding) can lead to missing intersections at shared endpoints.; Floating point precision issues can cause incorrect intersection detection or ordering of segments.
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
# - Circle-Circle Intersection (geometry, number, simulation, enumeration)
#   • When to use: Use this algorithm to find the common points where two circles intersect on a 2D plane, handling cases from no intersection to infinite points.
#   • Idea: This algorithm determines the intersection points of two circles by algebraically transforming their equations into a system involving one circle and one line. It typically achieves O(1) time complexity for finding the intersection points.
#   • Invariants: The relative positions and radii of the circles remain unchanged after coordinate translation.; The derived linear equation represents the radical axis of the two circles.
#   • Tips: Translate one circle to the origin to simplify the equations.; Subtract the two circle equations to derive a linear equation (the radical axis).
#   • Pitfalls: Numerical instability due to floating-point arithmetic, especially for tangent cases.; Forgetting to translate the resulting intersection points back to the original coordinate system.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numPoints(self, darts, r):
        """
        :type darts: List[List[int]]
        :type r: int
        :rtype: int
        """
        def dist2(p1, p2):
            return (p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2

        def circle_circle_intersection(c1, c2, r):
            d = math.sqrt(dist2(c1, c2))
            if d > 2 * r or d == 0:
                return []
            a = d / 2
            h = math.sqrt(r * r - a * a)
            mid = [(c1[0] + c2[0]) / 2, (c1[1] + c2[1]) / 2]
            offset = [h * (c2[1] - c1[1]) / d, h * (c1[0] - c2[0]) / d]
            return [[mid[0] + offset[0], mid[1] + offset[1]], [mid[0] - offset[0], mid[1] - offset[1]]]

        max_count = 1
        for i in range(len(darts)):
            for j in range(i + 1, len(darts)):
                intersections = circle_circle_intersection(darts[i], darts[j], r)
                for center in intersections:
                    count = sum(dist2(center, dart) <= r * r for dart in darts)
                    max_count = max(max_count, count)

        return max_count