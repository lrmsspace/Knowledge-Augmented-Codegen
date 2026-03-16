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
# - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
#   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
#   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
#   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
#   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
#   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
# - Sqrt Tree (array, tree, divide-and-conquer, recursion, prefix-sum)
#   • When to use: When performing associative range queries on an array, especially when O(1) query time is critical and O(N log log N) preprocessing is acceptable.
#   • Idea: The Sqrt Tree is a data structure that answers associative range queries on an array in O(1) time after O(N log log N) preprocessing. It achieves this by recursively applying sqrt decomposition, precomputing block-wise prefix/suffix operations and inter-block results.
#   • Invariants: The `prefixOp` array for any block `k` stores the associative sum from the block's start to each element within it.; The `suffixOp` array for any block `k` stores the associative sum from each element within it to the block's end.
#   • Tips: Ensure the operation is strictly associative for correctness.; Carefully handle block boundaries and partial blocks during query processing.
#   • Pitfalls: Using non-associative operations will yield incorrect results.; High memory usage for the 'between' array if not optimized or if N is very large.
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
        # Step 1: Create events for the sweep line algorithm
        events = []
        for x, y, l in squares:
            events.append((y, 'start', x, x + l))  # Start of a square
            events.append((y + l, 'end', x, x + l))  # End of a square

        # Step 2: Sort events by y-coordinate (and type to ensure starts come before ends)
        events.sort(key=lambda e: (e[0], e[1] == 'end'))

        # Step 3: Sweep line to calculate area above and below the line
        active_intervals = []
        last_y = 0
        area_below = 0
        area_above = 0

        for y, typ, x_start, x_end in events:
            if active_intervals:
                # Calculate the total length covered by active intervals
                active_intervals.sort()
                merged_length = 0
                current_start, current_end = active_intervals[0]

                for start, end in active_intervals[1:]:
                    if start > current_end:
                        merged_length += current_end - current_start
                        current_start, current_end = start, end
                    else:
                        current_end = max(current_end, end)

                merged_length += current_end - current_start

                # Update areas based on the last y-coordinate
                if y > last_y:
                    area_below += merged_length * (y - last_y)

            # Update active intervals based on event type
            if typ == 'start':
                active_intervals.append((x_start, x_end))
            else:
                active_intervals.remove((x_start, x_end))

            last_y = y

        # Step 4: Calculate total area and find the minimum y-coordinate for equal split
        total_area = area_below + area_above
        target_area = total_area / 2

        if target_area == 0:
            return float(last_y)  # If there's no area, any line works

        low, high = 0.0, float(last_y)
        while high - low > 1e-5:
            mid = (low + high) / 2
            area_below_mid = self.calculate_area_below(events, mid)

            if area_below_mid < target_area:
                low = mid
            else:
                high = mid
        return (low + high) / 2