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
# - Sqrt Decomposition (array, enumeration, prefix-sum)
#   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
#   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
#   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
#   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
#   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
# - Sqrt Decomposition (array, enumeration, difference-array)
#   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
#   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
#   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
#   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
#   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
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
        from collections import defaultdict
        import bisect

        # Group rectangles by height
        height_to_lengths = defaultdict(list)
        for length, height in rectangles:
            height_to_lengths[height].append(length)

        # Sort lengths for each height
        for height in height_to_lengths:
            height_to_lengths[height].sort()

        # Prepare sorted heights for binary search
        sorted_heights = sorted(height_to_lengths.keys())

        result = []
        for x, y in points:
            count = 0
            # Find the index of the first height that is >= y
            idx = bisect.bisect_left(sorted_heights, y)
            # Iterate through all heights that are >= y
            for h in sorted_heights[idx:]:
                lengths = height_to_lengths[h]
                # Count how many lengths are >= x using binary search
                count += len(lengths) - bisect.bisect_left(lengths, x)
            result.append(count)

        return result