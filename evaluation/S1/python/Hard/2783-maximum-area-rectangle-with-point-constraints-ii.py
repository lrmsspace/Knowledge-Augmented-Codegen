# Source: https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-ii/   |   Difficulty: Hard
#
# Problem Description:
# There are n points on an infinite plane. You are given two integer arrays xCoord and yCoord where (xCoord[i], yCoord[i]) represents the coordinates of the ith point.
#
# Your task is to find the maximum area of a rectangle that:
#
#
# 	Can be formed using four of these points as its corners.
# 	Does not contain any other point inside or on its border.
# 	Has its edges parallel to the axes.
#
#
# Return the maximum area that you can obtain or -1 if no such rectangle is possible.
#
# Example:
# Input: xCoord = [1,1,3,3], yCoord = [1,3,1,3]
#
# Output: 4
#
# Explanation:
#
#
#
# We can make a rectangle with these 4 points as corners and there is no other point that lies inside or on the border. Hence, the maximum possible area would be 4.
#
# Constraints:
# 1 <= xCoord.length == yCoord.length <= 2 * 105
# 	0 <= xCoord[i], yCoord[i] <= 8 * 107
# 	All the given points are unique.
#
# Helpful references (internal KB):
# - Segment Tree (tree, array, segment-tree, divide-and-conquer)
#   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
#   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
#   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
#   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
#   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
# - Point location in O(logn) (geometry, ds, simulation)
#   • When to use: Use when needing to efficiently determine which region (face or edge) of a planar subdivision a given query point lies within, especially for multiple online queries.
#   • Idea: This algorithm preprocesses a planar subdivision to answer point location queries in logarithmic time. It typically involves building a specialized data structure, possibly persistent, to quickly identify the containing face or edge for any given point.
#   • Invariants: The search process always maintains the invariant that the query point is within the current candidate region.; After each step, the search space for the point's location is reduced by a constant factor.
#   • Tips: Use a suitable geometric data structure like a trapezoidal map or persistent segment tree.; Carefully handle points lying exactly on edges or vertices.
#   • Pitfalls: Degenerate cases (vertical edges, collinear points) require careful handling.; Floating-point precision errors can lead to incorrect classifications.
# - Lattice points inside non-lattice polygon (geometry, number, counting, recursion)
#   • When to use: Use this when you need to count integer coordinate points strictly inside a polygon whose vertices are not restricted to integer coordinates. It's suitable for problems requiring precise geometric counting with non-lattice boundaries.
#   • Idea: This algorithm counts lattice points within a polygon with arbitrary vertices by summing signed contributions from each edge. It reduces the problem to evaluating sums of floor functions, sum(floor(kx+b)), which is solved recursively, typically achieving logarithmic complexity per edge.
#   • Invariants: The sum sum(floor(kx+b)) correctly accumulates points below the current edge segment.; After coordinate transformations, the problem reduces to a sum over a non-negative range with non-negative k and b.
#   • Tips: Decompose the polygon into signed areas under each edge, similar to the shoelace formula.; Handle edge cases where k or b are negative by appropriate transformations.
#   • Pitfalls: Floating point precision issues when calculating k and b or during transformations.; Incorrectly handling boundary points (points on edges or vertices).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxRectangleArea(self, xCoord, yCoord):
        """
        :type xCoord: List[int]
        :type yCoord: List[int]
        :rtype: int
        """
        # Step 1: Combine x and y coordinates into a list of points
        points = list(zip(xCoord, yCoord))
        point_set = set(points)  # For O(1) lookups

        max_area = -1
        n = len(points)

        # Step 2: Iterate through all pairs of points to find potential opposite corners of the rectangle
        for i in range(n):
            for j in range(i + 1, n):
                p1 = points[i]
                p2 = points[j]

                # Check if p1 and p2 can be opposite corners of a rectangle
                if p1[0] != p2[0] and p1[1] != p2[1]:  # Ensure they are not on the same line
                    # Calculate the coordinates of the other two corners
                    p3 = (p1[0], p2[1])  # (x1, y2)
                    p4 = (p2[0], p1[1])  # (x2, y1)

                    # Check if both p3 and p4 exist in the point set
                    if p3 in point_set and p4 in point_set:
                        # Calculate the area of the rectangle
                        area = abs(p2[0] - p1[0]) * abs(p2[1] - p1[1])
                        max_area = max(max_area, area)

        return max_area