# Source: https://leetcode.com/problems/maximum-points-inside-the-square/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D array points and a string s where, points[i] represents the coordinates of point i, and s[i] represents the tag of point i.
#
# A valid square is a square centered at the origin (0, 0), has edges parallel to the axes, and does not contain two points with the same tag.
#
# Return the maximum number of points contained in a valid square.
#
# Note:
#
#
# 	A point is considered to be inside the square if it lies on or within the square's boundaries.
# 	The side length of the square can be zero.
#
# Example:
# Input: points = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], s = "abdca"
#
# Output: 2
#
# Explanation:
#
# The square of side length 4 covers two points points[0] and points[1].
#
# Constraints:
# 1 <= s.length, points.length <= 105
# 	points[i].length == 2
# 	-109 <= points[i][0], points[i][1] <= 109
# 	s.length == points.length
# 	points consists of distinct coordinates.
# 	s consists only of lowercase English letters.
#
# Helpful references (internal KB):
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
# - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
#   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
#   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
#   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
#   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
#   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
# - Convex Hull construction (geometry, array, enumeration)
#   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
#   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
#   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
#   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
#   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxPointsInsideSquare(self, points, s):
        """
        :type points: List[List[int]]
        :type s: str
        :rtype: int
        """
        # Step 1: Transform coordinates to (x+y, x-y)
        transformed_points = [(x + y, x - y, tag) for (x, y), tag in zip(points, s)]

        # Step 2: Sort points by x+y and then by x-y
        transformed_points.sort(key=lambda p: (p[0], p[1]))

        max_points = 0
        left = 0
        seen_tags = set()

        # Step 3: Use two pointers to find the largest valid square
        for right in range(len(transformed_points)):
            while transformed_points[right][0] - transformed_points[left][0] > 2 * max_points:
                if transformed_points[left][2] in seen_tags:
                    seen_tags.remove(transformed_points[left][2])
                left += 1
            if transformed_points[right][2] in seen_tags:
                break
            seen_tags.add(transformed_points[right][2])
            max_points = max(max_points, len(seen_tags))
        return max_points