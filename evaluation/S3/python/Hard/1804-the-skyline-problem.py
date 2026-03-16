# Source: https://leetcode.com/problems/the-skyline-problem/   |   Difficulty: Hard
#
# Problem Description:
# A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return the skyline formed by these buildings collectively.
#
# The geometric information of each building is given in the array buildings where buildings[i] = [lefti, righti, heighti]:
#
#
# 	lefti is the x coordinate of the left edge of the ith building.
# 	righti is the x coordinate of the right edge of the ith building.
# 	heighti is the height of the ith building.
#
#
# You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.
#
# The skyline should be represented as a list of "key points" sorted by their x-coordinate in the form [[x1,y1],[x2,y2],...]. Each key point is the left endpoint of some horizontal segment in the skyline except the last point in the list, which always has a y-coordinate 0 and is used to mark the skyline's termination where the rightmost building ends. Any ground between the leftmost and rightmost buildings should be part of the skyline's contour.
#
# Note: There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...,[2 3],[4 5],[12 7],...]
#
# Example:
# Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
# Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
# Explanation:
# Figure A shows the buildings of the input.
# Figure B shows the skyline formed by those buildings. The red points in figure B represent the key points in the output list.
#
# Constraints:
# 1 <= buildings.length <= 104
# 	0 <= lefti < righti <= 231 - 1
# 	1 <= heighti <= 231 - 1
# 	buildings is sorted by lefti in non-decreasing order.
#
# Helpful references (internal KB):
# - Search for a pair of intersecting segments (geometry, enumeration, sweep-line)
#   • When to use: When needing to efficiently detect if any two line segments among a given set intersect, or to find one such intersecting pair.
#   • Idea: This algorithm efficiently determines if any two line segments in a given set intersect by processing events along a sweep line, typically achieving O(N log N) time complexity.
#   • Invariants: All segments fully to the left of the sweep line have been processed and do not intersect each other.; The active set contains all segments currently intersecting the sweep line, ordered by their y-coordinate.
#   • Tips: Represent segments by their endpoints as event points, sorted by x-coordinate.; Use a balanced binary search tree (or similar structure) to maintain active segments ordered by their y-coordinate at the sweep line.
#   • Pitfalls: Floating point precision issues can lead to incorrect intersection detection or ordering.; Degenerate cases like collinear segments or multiple segments intersecting at a single point.
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
    def getSkyline(self, buildings):
        """
        :type buildings: List[List[int]]
        :rtype: List[List[int]]
        """
        import heapq

        # Create a list of events for the sweep line
        events = []
        for left, right, height in buildings:
            events.append((left, -height))  # Start of a building
            events.append((right, height))  # End of a building

        # Sort events: first by x-coordinate, then by height
        events.sort(key=lambda x: (x[0], x[1]))

        result = []
        max_heap = [0]  # Max-heap to keep track of active building heights
        prev_max_height = 0

        for x, h in events:
            if h < 0:  # Start of a building
                heapq.heappush(max_heap, h)
            else:  # End of a building
                max_heap.remove(-h)  # Remove the corresponding start height
                heapq.heapify(max_heap)  # Re-heapify after removal

            current_max_height = -max_heap[0]  # Current tallest building
            if current_max_height != prev_max_height:
                result.append([x, current_max_height])  # Add key point to result
                prev_max_height = current_max_height

        return result