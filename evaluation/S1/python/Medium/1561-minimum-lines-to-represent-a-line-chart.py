# Source: https://leetcode.com/problems/minimum-lines-to-represent-a-line-chart/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D integer array stockPrices where stockPrices[i] = [dayi, pricei] indicates the price of the stock on day dayi is pricei. A line chart is created from the array by plotting the points on an XY plane with the X-axis representing the day and the Y-axis representing the price and connecting adjacent points. One such example is shown below:
#
# Return the minimum number of lines needed to represent the line chart.
#
# Example:
# Input: stockPrices = [[1,7],[2,6],[3,5],[4,4],[5,4],[6,3],[7,2],[8,1]]
# Output: 3
# Explanation:
# The diagram above represents the input, with the X-axis representing the day and Y-axis representing the price.
# The following 3 lines can be drawn to represent the line chart:
# - Line 1 (in red) from (1,7) to (4,4) passing through (1,7), (2,6), (3,5), and (4,4).
# - Line 2 (in blue) from (4,4) to (5,4).
# - Line 3 (in green) from (5,4) to (8,1) passing through (5,4), (6,3), (7,2), and (8,1).
# It can be shown that it is not possible to represent the line chart using less than 3 lines.
#
# Constraints:
# 1 <= stockPrices.length <= 105
# 	stockPrices[i].length == 2
# 	1 <= dayi, pricei <= 109
# 	All dayi are distinct.
#
# Helpful references (internal KB):
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Convex hull trick and Li Chao tree (number, segment-tree, recursion)
#   • When to use: Used to find the minimum (or maximum) value among a set of linear functions at a given point. It is particularly efficient for dynamic sets of lines or when slopes are monotonic.
#   • Idea: The Convex Hull Trick (CHT) and Li Chao Tree efficiently find the minimum (or maximum) value of a set of linear functions at a query point. CHT typically achieves O(log N) or O(1) amortized time, while Li Chao Tree offers O(log C) for updates and queries.
#   • Invariants: In CHT, the lower envelope of lines forms a convex shape, with slopes monotonically ordered.; In Li Chao Tree, each node stores a line that is optimal at the segment's midpoint for lines added to that node.
#   • Tips: Ensure slopes are monotonic for efficient CHT implementations.; Li Chao Tree handles non-monotonic slopes but requires a coordinate range.
#   • Pitfalls: Floating point precision issues can lead to incorrect intersection calculations.; Incorrectly managing the convex hull structure (e.g., deque) in CHT.
# - Convex Hull construction (geometry, array, stack, sweep-line, monotonic-stack)
#   • When to use: When you need to find the smallest convex polygon enclosing a given set of points. It's used for problems requiring the outermost boundary of a point set.
#   • Idea: Convex Hull construction algorithms, like Graham Scan or Monotone Chain, find the smallest convex polygon that encloses a given set of points. These algorithms typically have a time complexity of O(N log N) due to sorting.
#   • Invariants: The points currently on the stack form a convex chain in the desired direction.; For any three consecutive points A, B, C on the stack, the turn from AB to BC maintains convexity.
#   • Tips: Use an orientation test (cross product) to determine if points make a clockwise or counter-clockwise turn.; Handle collinear points carefully, especially if they need to be included in the hull.
#   • Pitfalls: Incorrectly handling collinear points can lead to an incomplete or incorrect hull.; Floating-point precision issues can affect orientation tests, leading to wrong turns.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumLines(self, stockPrices):
        """
        :type stockPrices: List[List[int]]
        :rtype: int
        """
        stockPrices.sort(key=lambda x: x[0])
        n = len(stockPrices)
        if n <= 2:
            return n - 1
        
        def slope(p1, p2):
            return (p2[1] - p1[1]) * 1.0 / (p2[0] - p1[0])
        
        lines = 1
        prev_slope = slope(stockPrices[0], stockPrices[1])
        
        for i in range(2, n):
            curr_slope = slope(stockPrices[i-1], stockPrices[i])
            if curr_slope != prev_slope:
                lines += 1
                prev_slope = curr_slope
        
        return lines