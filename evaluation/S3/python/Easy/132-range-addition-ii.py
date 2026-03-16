# Source: https://leetcode.com/problems/range-addition-ii/   |   Difficulty: Easy
#
# Problem Description:
# You are given an m x n matrix M initialized with all 0's and an array of operations ops, where ops[i] = [ai, bi] means M[x][y] should be incremented by one for all 0 <= x < ai and 0 <= y < bi.
#
# Count and return the number of maximum integers in the matrix after performing all the operations.
#
# Example:
# Input: m = 3, n = 3, ops = [[2,2],[3,3]]
# Output: 4
# Explanation: The maximum integer in M is 2, and there are four of it in M. So return 4.
#
# Constraints:
# 1 <= m, n <= 4 * 104
# 	0 <= ops.length <= 104
# 	ops[i].length == 2
# 	1 <= ai <= m
# 	1 <= bi <= n
#
# Helpful references (internal KB):
# - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
#   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
#   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
#   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
#   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
#   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
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
    def maxCount(self, m, n, ops):
        """
        :type m: int
        :type n: int
        :type ops: List[List[int]]
        :rtype: int
        """
        if not ops:
            return m * n
        
        min_a = min(op[0] for op in ops)
        min_b = min(op[1] for op in ops)
        
        return min_a * min_b