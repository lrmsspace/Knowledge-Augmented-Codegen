# Source: https://leetcode.com/problems/separate-squares-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
#
# Find the minimum y-coordinate value of a horizontal line such that the total area covered by squares above the line equals the total area covered by squares below the line.
#
# Answers within 10-5 of the actual answer will be accepted.
#
# Note: Squares may overlap. Overlapping areas should be counted only once in this version.
#
# Example:
# Input: squares = [[0,0,1],[2,2,1]]
#
# Output: 1.00000
#
# Explanation:
#
#
#
# Any horizontal line between y = 1 and y = 2 results in an equal split, with 1 square unit above and 1 square unit below. The minimum y-value is 1.
#
# Constraints:
# 1 <= squares.length <= 5 * 104
# 	squares[i] = [xi, yi, li]
# 	squares[i].length == 3
# 	0 <= xi, yi <= 109
# 	1 <= li <= 109
# 	The total area of all the squares will not exceed 1015.
#
# Helpful references (internal KB):
# - Length of the union of segments (array, interval, sweep-line, counting)
#   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
#   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
#   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
#   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
#   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
# - Search for a pair of intersecting segments (tree, geometry, sweep-line, counting)
#   • When to use: Use this algorithm to efficiently determine if any pair of line segments in a given set intersect. It is particularly effective for detecting geometric overlaps in a 2D plane.
#   • Idea: This algorithm processes segments by sweeping a vertical line across the plane, maintaining an ordered set of active segments to efficiently check for intersections with neighbors. It achieves an optimal time complexity of O(N log N).
#   • Invariants: The sweep line always moves from left to right, processing events in increasing x-coordinate order.; The set of active segments contains all segments currently intersected by the sweep line, ordered by their y-coordinate at the sweep line's current x-position.
#   • Tips: Process events at the same x-coordinate by adding segments before removing them to catch vertex intersections.; Use a balanced binary search tree (e.g., `std::set`) to maintain active segments, ordered by their y-coordinate.
#   • Pitfalls: Incorrect event ordering (e.g., removing before adding) can lead to missing intersections at shared endpoints.; Floating point precision issues can cause incorrect intersection detection or ordering of segments.
# - Search for a pair of intersecting segments (geometry, enumeration, sweep-line)
#   • When to use: When needing to efficiently detect if any two line segments among a given set intersect, or to find one such intersecting pair.
#   • Idea: This algorithm efficiently determines if any two line segments in a given set intersect by processing events along a sweep line, typically achieving O(N log N) time complexity.
#   • Invariants: All segments fully to the left of the sweep line have been processed and do not intersect each other.; The active set contains all segments currently intersecting the sweep line, ordered by their y-coordinate.
#   • Tips: Represent segments by their endpoints as event points, sorted by x-coordinate.; Use a balanced binary search tree (or similar structure) to maintain active segments ordered by their y-coordinate at the sweep line.
#   • Pitfalls: Floating point precision issues can lead to incorrect intersection detection or ordering.; Degenerate cases like collinear segments or multiple segments intersecting at a single point.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def separateSquares(self, squares):
        """
        :type squares: List[List[int]]
        :rtype: float
        """
        # Step 1: Collect all unique y-coordinates from the squares
        y_coords = set()
        for x, y, l in squares:
            y_coords.add(y)       # bottom edge
            y_coords.add(y + l)   # top edge

        # Step 2: Sort the unique y-coordinates
        sorted_y = sorted(y_coords)

        # Step 3: Calculate the area covered by squares above and below each horizontal line defined by sorted_y
        total_area = self.calculate_total_area(squares)
        area_below = 0
        area_above = total_area

        for i in range(len(sorted_y) - 1):
            current_y = sorted_y[i]
            next_y = sorted_y[i + 1]

            # Calculate the area of squares between current_y and next_y
            area_between = self.calculate_area_between(squares, current_y, next_y)

            area_below += area_between
            area_above -= area_between

            if abs(area_below - area_above) < 1e-5:
                return float(current_y)

        return -1.0  # If no such line exists