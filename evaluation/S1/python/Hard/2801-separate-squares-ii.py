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
# - Search for a pair of intersecting segments (tree, geometry, sweep-line, counting)
#   • When to use: Use this algorithm to efficiently determine if any pair of line segments in a given set intersect. It is particularly effective for detecting geometric overlaps in a 2D plane.
#   • Idea: This algorithm processes segments by sweeping a vertical line across the plane, maintaining an ordered set of active segments to efficiently check for intersections with neighbors. It achieves an optimal time complexity of O(N log N).
#   • Invariants: The sweep line always moves from left to right, processing events in increasing x-coordinate order.; The set of active segments contains all segments currently intersected by the sweep line, ordered by their y-coordinate at the sweep line's current x-position.
#   • Tips: Process events at the same x-coordinate by adding segments before removing them to catch vertex intersections.; Use a balanced binary search tree (e.g., `std::set`) to maintain active segments, ordered by their y-coordinate.
#   • Pitfalls: Incorrect event ordering (e.g., removing before adding) can lead to missing intersections at shared endpoints.; Floating point precision issues can cause incorrect intersection detection or ordering of segments.
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
# - Manhattan Distance (geometry, graph, sweep-line, mst-kruskal, coordinate-compress)
#   • When to use: Use this when finding the Minimum Spanning Tree for points in a 2D plane where edge weights are Manhattan distances, or when a geometric problem can be simplified by transforming Manhattan to Chebyshev distance.
#   • Idea: This algorithm finds the Minimum Spanning Tree for points in a 2D plane using Manhattan distance. It leverages a sweep-line approach to efficiently find nearest neighbors in specific octants, reducing the number of candidate edges for Kruskal's algorithm, achieving O(N log N) complexity.
#   • Invariants: For any point 's' in the active set, its nearest neighbor in the current octant has not yet been processed.; Points are processed in non-decreasing order of 'x + y' (or transformed coordinate), ensuring local optimality for distances.
#   • Tips: Consider transforming Manhattan distance problems into Chebyshev distance problems using (x+y, y-x) coordinates.; Divide the plane into 8 octants around each point to simplify nearest neighbor searches.
#   • Pitfalls: Incorrectly defining or handling the 8 octants, especially near boundaries or for points with equal coordinates.; Inefficiently managing the 'active set' during the sweep-line, leading to higher than O(N log N) complexity.
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
        def area_below_line(y_line):
            events = []
            for x, y, l in squares:
                if y + l <= y_line:
                    # Entire square is below the line
                    events.append((x, 'start', y, y + l))
                    events.append((x + l, 'end', y, y + l))
                elif y < y_line < y + l:
                    # Square is partially below the line
                    events.append((x, 'start', y, y_line))
                    events.append((x + l, 'end', y, y_line))

            events.sort()
            active_intervals = []
            prev_x = None
            total_area = 0

            for x, typ, y_start, y_end in events:
                if prev_x is not None and active_intervals:
                    # Calculate the covered length in the y-direction
                    covered_length = 0
                    current_start = -1
                    current_end = -1

                    for start, end in sorted(active_intervals):
                        if start > current_end:
                            covered_length += current_end - current_start
                            current_start, current_end = start, end
                        else:
                            current_end = max(current_end, end)

                    covered_length += current_end - current_start
                    total_area += covered_length * (x - prev_x)

                if typ == 'start':
                    active_intervals.append((y_start, y_end))
                else:
                    active_intervals.remove((y_start, y_end))

                prev_x = x

            return total_area

        low, high = 0.0, 1e9 + 1.0
        total_area = sum(l * l for _, _, l in squares)

        for _ in range(100):
            mid = (low + high) / 2.0
            if area_below_line(mid) * 2 < total_area:
                low = mid
            else:
                high = mid

        return low
            