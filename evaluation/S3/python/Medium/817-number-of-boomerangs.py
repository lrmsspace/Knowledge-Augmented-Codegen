# Source: https://leetcode.com/problems/number-of-boomerangs/   |   Difficulty: Medium
#
# Problem Description:
# You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
#
# Return the number of boomerangs.
#
# Example:
# Input: points = [[0,0],[1,0],[2,0]]
# Output: 2
# Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
#
# Constraints:
# n == points.length
# 	1 <= n <= 500
# 	points[i].length == 2
# 	-104 <= xi, yi <= 104
# 	All the points are unique.
#
# Helpful references (internal KB):
# - Convex Hull construction (geometry, array, enumeration)
#   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
#   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
#   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
#   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
#   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
# - Minimum Enclosing Circle (geometry, number, simulation)
#   • When to use: When you need to find the smallest circle that contains all given points in a 2D plane, often with a requirement for expected linear time complexity.
#   • Idea: This algorithm iteratively constructs the Minimum Enclosing Circle (MEC) by considering points one by one, potentially updating the circle if a new point lies outside. It achieves an expected linear time complexity, O(N), through randomization.
#   • Invariants: The current circle C is the MEC for the subset of points processed so far.; If C is defined by 1 point p_i, it is the MEC of points processed so far that passes through p_i.
#   • Tips: Randomly shuffle input points to achieve expected linear time complexity.; The Minimum Enclosing Circle is always defined by 2 or 3 points on its boundary.
#   • Pitfalls: A naive implementation without randomization can lead to O(N^3) worst-case time complexity.; Floating-point precision issues can arise in geometric calculations, requiring careful handling.
# - Minimum Enclosing Circle (array, geometry, randomized, recursion)
#   • When to use: Use when finding the smallest circle that contains a given set of 2D points. It provides an expected linear time solution for this fundamental geometric problem.
#   • Idea: Welzl's algorithm finds the unique minimum enclosing circle for a set of points using a randomized incremental approach. It achieves an expected time complexity of O(N).
#   • Invariants: The current candidate circle `C` encloses all points `p_1, ..., p_i` processed so far.; If `p_i` is not contained in `C_{i-1}`, then `p_i` must lie on the boundary of `C_i`.
#   • Tips: Randomly permute input points to ensure expected O(N) performance.; The MEC is uniquely determined by either two points forming a diameter or three points on its boundary.
#   • Pitfalls: Not randomizing the input can lead to a worst-case O(N^3) performance.; Floating-point precision issues can cause incorrect boundary checks or point containment tests.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfBoomerangs(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict
        
        def distance(p1, p2):
            return (p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2
        
        boomerangs = 0
        
        for i in range(len(points)):
            dist_count = defaultdict(int)
            for j in range(len(points)):
                if i != j:
                    d = distance(points[i], points[j])
                    dist_count[d] += 1
            
            for count in dist_count.values():
                if count > 1:
                    boomerangs += count * (count - 1)  # P(count, 2)
        
        return boomerangs