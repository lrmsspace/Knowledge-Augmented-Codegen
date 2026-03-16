# Source: https://leetcode.com/problems/count-number-of-rectangles-containing-each-point/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D integer array rectangles where rectangles[i] = [li, hi] indicates that ith rectangle has a length of li and a height of hi. You are also given a 2D integer array points where points[j] = [xj, yj] is a point with coordinates (xj, yj).
#
# The ith rectangle has its bottom-left corner point at the coordinates (0, 0) and its top-right corner point at (li, hi).
#
# Return an integer array count of length points.length where count[j] is the number of rectangles that contain the jth point.
#
# The ith rectangle contains the jth point if 0 <= xj <= li and 0 <= yj <= hi. Note that points that lie on the edges of a rectangle are also considered to be contained by that rectangle.
#
# Example:
# Input: rectangles = [[1,2],[2,3],[2,5]], points = [[2,1],[1,4]]
# Output: [2,1]
# Explanation: 
# The first rectangle contains no points.
# The second rectangle contains only the point (2, 1).
# The third rectangle contains the points (2, 1) and (1, 4).
# The number of rectangles that contain the point (2, 1) is 2.
# The number of rectangles that contain the point (1, 4) is 1.
# Therefore, we return [2, 1].
#
# Constraints:
# 1 <= rectangles.length, points.length <= 5 * 104
# 	rectangles[i].length == points[j].length == 2
# 	1 <= li, xj <= 109
# 	1 <= hi, yj <= 100
# 	All the rectangles are unique.
# 	All the points are unique.
#
# Helpful references (internal KB):
# - Length of the union of segments (array, interval, sweep-line, counting)
#   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
#   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
#   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
#   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
#   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
# - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
#   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
#   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
#   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
#   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
#   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
# - Check if point belongs to the convex pol (geometry, array, binary-search)
#   • When to use: This algorithm is used to efficiently determine if a given query point lies inside or on the boundary of a convex polygon, especially when many queries are performed on the same polygon.
#   • Idea: The core idea is to decompose the convex polygon into triangles originating from a reference vertex. Binary search is then used to find the specific triangle that could contain the query point, followed by a point-in-triangle check.
#   • Invariants: The reference point p_0 is the lexicographically smallest vertex of the polygon.; All polygon vertices p_1, ..., p_n are ordered counter-clockwise by polar angle around p_0.
#   • Tips: Choose a consistent reference point, typically the lexicographically smallest vertex, to simplify angular sorting.; Ensure polygon vertices are ordered (e.g., counter-clockwise) relative to the reference point for correct binary search behavior.
#   • Pitfalls: Floating point precision errors can lead to incorrect results for collinear points or boundary checks; prefer integer arithmetic with cross products.; Incorrectly handling boundary conditions (points exactly on an edge or vertex) can lead to false negatives or positives.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countRectangles(self, rectangles, points):
        """
        :type rectangles: List[List[int]]
        :type points: List[List[int]]
        :rtype: List[int]
        """
        # Group rectangles by height
        height_to_lengths = {}
        for length, height in rectangles:
            if height not in height_to_lengths:
                height_to_lengths[height] = []
            height_to_lengths[height].append(length)

        # Sort lengths for each height
        for height in height_to_lengths:
            height_to_lengths[height].sort()

        # Prepare sorted heights
        sorted_heights = sorted(height_to_lengths.keys())

        result = []
        for x, y in points:
            count = 0
            # For each point, count rectangles that can contain it
            for height in sorted_heights:
                if height < y:
                    continue  # Skip heights that are too small
                lengths = height_to_lengths[height]
                # Count how many lengths are >= x using binary search
                left, right = 0, len(lengths)
                while left < right:
                    mid = (left + right) // 2
                    if lengths[mid] >= x:
                        right = mid
                    else:
                        left = mid + 1
                count += len(lengths) - left  # All lengths from 'left' to end are valid
            result.append(count)

        return result