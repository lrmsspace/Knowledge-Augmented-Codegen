# Source: https://leetcode.com/problems/perfect-rectangle/   |   Difficulty: Hard
#
# Problem Description:
# Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).
#
# Return true if all the rectangles together form an exact cover of a rectangular region.
#
# Example:
# Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
# Output: true
# Explanation: All 5 rectangles together form an exact cover of a rectangular region.
#
# Constraints:
# 1 <= rectangles.length <= 2 * 104
# 	rectangles[i].length == 4
# 	-105 <= xi < ai <= 105
# 	-105 <= yi < bi <= 105
#
# Helpful references (internal KB):
# - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
#   • When to use: Use when calculating the area of a simple polygon given its vertices in order. It is efficient for both convex and non-convex polygons.
#   • Idea: This algorithm calculates the area of a simple polygon by summing signed trapezoidal areas formed by each edge and the x-axis, or equivalently, using the shoelace formula. It achieves an optimal O(N) time complexity, where N is the number of vertices.
#   • Invariants: Vertices are processed sequentially in their given order, forming edges.; The running sum `current_sum` accumulates the signed contribution from each edge processed so far.
#   • Tips: Ensure vertices are provided in a consistent order (clockwise or counter-clockwise).; Use a data type with sufficient range (e.g., long long or double) for intermediate sums to prevent overflow.
#   • Pitfalls: Incorrect vertex order will result in an incorrect signed area or even zero.; Integer overflow can occur if coordinates are large and sums exceed standard integer limits.
# - Half-plane intersection (geometry, simulation)
#   • When to use: When you need to find the common region defined by a set of half-planes, or determine if such a region exists. It's particularly useful for checking if the intersection is empty.
#   • Idea: This method finds the intersection of N half-planes by checking all O(N^2) pairwise line intersections. Each intersection point is then verified against all N half-planes, resulting in an O(N^3) time complexity.
#   • Invariants: Each candidate vertex is an intersection of two half-plane boundary lines.; Any point included in the final intersection region satisfies all given half-plane constraints.
#   • Tips: The vertices of the resulting convex polygon are always intersection points of the boundary lines.; Can be used to check if the intersection region is empty.
#   • Pitfalls: High time complexity of O(N^3) makes it inefficient for large N.; Numerical precision issues when calculating intersection points and checking containment.
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isRectangleCover(self, rectangles):
        """
        :type rectangles: List[List[int]]
        :rtype: bool
        """
        # Step 1: Calculate the area of the bounding rectangle and the sum of areas of all rectangles
        min_x = min(rect[0] for rect in rectangles)
        min_y = min(rect[1] for rect in rectangles)
        max_x = max(rect[2] for rect in rectangles)
        max_y = max(rect[3] for rect in rectangles)

        bounding_area = (max_x - min_x) * (max_y - min_y)
        total_area = sum((rect[2] - rect[0]) * (rect[3] - rect[1]) for rect in rectangles)

        if bounding_area != total_area:
            return False

        # Step 2: Use a set to track the corners of the rectangles
        corners = set()
        for x1, y1, x2, y2 in rectangles:
            corners ^= {(x1, y1), (x1, y2), (x2, y1), (x2, y2)}

        # Step 3: Check if the corners set contains exactly the four corners of the bounding rectangle
        expected_corners = {(min_x, min_y), (min_x, max_y), (max_x, min_y), (max_x, max_y)}
        return corners == expected_corners