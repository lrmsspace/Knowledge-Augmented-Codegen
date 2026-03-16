# Source: https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n representing the dimensions of an n x n grid, with the origin at the bottom-left corner of the grid. You are also given a 2D array of coordinates rectangles, where rectangles[i] is in the form [startx, starty, endx, endy], representing a rectangle on the grid. Each rectangle is defined as follows:
#
#
# 	(startx, starty): The bottom-left corner of the rectangle.
# 	(endx, endy): The top-right corner of the rectangle.
#
#
# Note that the rectangles do not overlap. Your task is to determine if it is possible to make either two horizontal or two vertical cuts on the grid such that:
#
#
# 	Each of the three resulting sections formed by the cuts contains at least one rectangle.
# 	Every rectangle belongs to exactly one section.
#
#
# Return true if such cuts can be made; otherwise, return false.
#
# Example:
# Input: n = 5, rectangles = [[1,0,5,2],[0,2,2,4],[3,2,5,3],[0,4,4,5]]
#
# Output: true
#
# Explanation:
#
#
#
# The grid is shown in the diagram. We can make horizontal cuts at y = 2 and y = 4. Hence, output is true.
#
# Constraints:
# 3 <= n <= 109
# 	3 <= rectangles.length <= 105
# 	0 <= rectangles[i][0] < rectangles[i][2] <= n
# 	0 <= rectangles[i][1] < rectangles[i][3] <= n
# 	No two rectangles overlap.
#
# Helpful references (internal KB):
# - Search for a pair of intersecting segments (tree, geometry, sweep-line, counting)
#   • When to use: Use this algorithm to efficiently determine if any pair of line segments in a given set intersect. It is particularly effective for detecting geometric overlaps in a 2D plane.
#   • Idea: This algorithm processes segments by sweeping a vertical line across the plane, maintaining an ordered set of active segments to efficiently check for intersections with neighbors. It achieves an optimal time complexity of O(N log N).
#   • Invariants: The sweep line always moves from left to right, processing events in increasing x-coordinate order.; The set of active segments contains all segments currently intersected by the sweep line, ordered by their y-coordinate at the sweep line's current x-position.
#   • Tips: Process events at the same x-coordinate by adding segments before removing them to catch vertex intersections.; Use a balanced binary search tree (e.g., `std::set`) to maintain active segments, ordered by their y-coordinate.
#   • Pitfalls: Incorrect event ordering (e.g., removing before adding) can lead to missing intersections at shared endpoints.; Floating point precision issues can cause incorrect intersection detection or ordering of segments.
# - Half-plane intersection (geometry, simulation)
#   • When to use: When you need to find the common region defined by a set of half-planes, or determine if such a region exists. It's particularly useful for checking if the intersection is empty.
#   • Idea: This method finds the intersection of N half-planes by checking all O(N^2) pairwise line intersections. Each intersection point is then verified against all N half-planes, resulting in an O(N^3) time complexity.
#   • Invariants: Each candidate vertex is an intersection of two half-plane boundary lines.; Any point included in the final intersection region satisfies all given half-plane constraints.
#   • Tips: The vertices of the resulting convex polygon are always intersection points of the boundary lines.; Can be used to check if the intersection region is empty.
#   • Pitfalls: High time complexity of O(N^3) makes it inefficient for large N.; Numerical precision issues when calculating intersection points and checking containment.
# - Minimum Spanning Trees (graph, greedy)
#   • When to use: When you need to find a subset of edges in a connected, edge-weighted graph that connects all vertices with the minimum possible total edge weight. Useful for network design problems where minimizing connection costs is crucial.
#   • Idea: A Minimum Spanning Tree (MST) algorithm finds a subset of edges in an edge-weighted graph that connects all vertices with the minimum possible total weight, forming a tree. This is typically solved using greedy approaches with a time complexity often involving sorting edges or using a priority queue.
#   • Invariants: The set of edges selected so far always forms a forest.; Each connected component formed by the chosen edges is a valid subtree of some Minimum Spanning Tree.
#   • Tips: Greedy approaches often work by iteratively adding the cheapest valid edge or expanding from a starting vertex.; The cut property and cycle property are fundamental for proving correctness of MST algorithms.
#   • Pitfalls: Assuming the graph is always connected; disconnected graphs require finding a minimum spanning forest.; Incorrectly applying the greedy choice without ensuring it maintains the MST property (e.g., creating a cycle).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def checkValidCuts(self, n, rectangles):
        """
        :type n: int
        :type rectangles: List[List[int]]
        :rtype: bool
        """
        horizontal_cuts = set()
        vertical_cuts = set()
        
        for startx, starty, endx, endy in rectangles:
            horizontal_cuts.add(starty)
            horizontal_cuts.add(endy)
            vertical_cuts.add(startx)
            vertical_cuts.add(endx)
        
        if len(horizontal_cuts) < 3 or len(vertical_cuts) < 3:
            return False
        
        return True