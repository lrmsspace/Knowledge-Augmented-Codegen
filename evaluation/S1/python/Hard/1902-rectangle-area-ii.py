# Source: https://leetcode.com/problems/rectangle-area-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D array of axis-aligned rectangles. Each rectangle[i] = [xi1, yi1, xi2, yi2] denotes the ith rectangle where (xi1, yi1) are the coordinates of the bottom-left corner, and (xi2, yi2) are the coordinates of the top-right corner.
#
# Calculate the total area covered by all rectangles in the plane. Any area covered by two or more rectangles should only be counted once.
#
# Return the total area. Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
# Output: 6
# Explanation: A total area of 6 is covered by all three rectangles, as illustrated in the picture.
# From (1,1) to (2,2), the green and red rectangles overlap.
# From (1,0) to (2,3), all three rectangles overlap.
#
# Constraints:
# 1 <= rectangles.length <= 200
# 	rectanges[i].length == 4
# 	0 <= xi1, yi1, xi2, yi2 <= 109
# 	xi1 <= xi2
# 	yi1 <= yi2
# 	All rectangles have non zero area.
#
# Helpful references (internal KB):
# - Search for a pair of intersecting segments (tree, geometry, sweep-line, counting)
#   • When to use: Use this algorithm to efficiently determine if any pair of line segments in a given set intersect. It is particularly effective for detecting geometric overlaps in a 2D plane.
#   • Idea: This algorithm processes segments by sweeping a vertical line across the plane, maintaining an ordered set of active segments to efficiently check for intersections with neighbors. It achieves an optimal time complexity of O(N log N).
#   • Invariants: The sweep line always moves from left to right, processing events in increasing x-coordinate order.; The set of active segments contains all segments currently intersected by the sweep line, ordered by their y-coordinate at the sweep line's current x-position.
#   • Tips: Process events at the same x-coordinate by adding segments before removing them to catch vertex intersections.; Use a balanced binary search tree (e.g., `std::set`) to maintain active segments, ordered by their y-coordinate.
#   • Pitfalls: Incorrect event ordering (e.g., removing before adding) can lead to missing intersections at shared endpoints.; Floating point precision issues can cause incorrect intersection detection or ordering of segments.
# - Length of the union of segments (array, interval, sweep-line, counting)
#   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
#   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
#   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
#   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
#   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
# - Segment Tree (tree, array, segment-tree)
#   • When to use: Use when you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in logarithmic time.
#   • Idea: A Segment Tree is a tree-based data structure that stores information about array intervals, enabling efficient O(log n) range queries and point/range updates.
#   • Invariants: Each node in the segment tree represents a contiguous subsegment of the original array.; The value stored in a non-leaf node is an aggregation of the values from its direct children.
#   • Tips: Build the tree recursively, dividing the array into halves.; Use lazy propagation for efficient range updates to avoid O(N) updates.
#   • Pitfalls: Off-by-one errors when defining segment boundaries or array indices.; Forgetting to push down lazy tags before querying or updating children nodes.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def rectangleArea(self, rectangles):
        """
        :type rectangles: List[List[int]]
        :rtype: int
        """
        # Step 1: Generate events for the sweep line algorithm
        events = []  # (x, type, y1, y2)
        for x1, y1, x2, y2 in rectangles:
            events.append((x1, 1, y1, y2))  # Starting edge
            events.append((x2, -1, y1, y2)) # Ending edge

        # Step 2: Sort events by x-coordinate
        events.sort()

        # Step 3: Active intervals and total area calculation
        active_intervals = []
        prev_x = 0
        total_area = 0
        MOD = 10**9 + 7

        def calculate_active_length():
            if not active_intervals:
                return 0
            active_intervals.sort()
            merged_length = 0
            current_start, current_end = active_intervals[0]

            for start, end in active_intervals[1:]:
                if start > current_end:  # No overlap
                    merged_length += current_end - current_start
                    current_start, current_end = start, end
                else:  # Overlap
                    current_end = max(current_end, end)

            merged_length += current_end - current_start  # Add last interval
            return merged_length

        for x, typ, y1, y2 in events:
            # Calculate area contribution from previous x to current x
            if prev_x != x:
                active_length = calculate_active_length()
                total_area += active_length * (x - prev_x)
                total_area %= MOD
                prev_x = x

            # Update active intervals based on event type
            if typ == 1:  # Starting edge
                active_intervals.append((y1, y2))
            else:          # Ending edge
                active_intervals.remove((y1, y2))

        return total_area