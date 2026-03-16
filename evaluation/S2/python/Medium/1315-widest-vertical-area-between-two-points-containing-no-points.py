# Source: https://leetcode.com/problems/widest-vertical-area-between-two-points-containing-no-points/   |   Difficulty: Medium
#
# Problem Description:
# Given n points on a 2D plane where points[i] = [xi, yi], Return the widest vertical area between two points such that no points are inside the area.
#
# A vertical area is an area of fixed-width extending infinitely along the y-axis (i.e., infinite height). The widest vertical area is the one with the maximum width.
#
# Note that points on the edge of a vertical area are not considered included in the area.
#
# Example:
# ​
#
# Input: points = [[8,7],[9,9],[7,4],[9,7]]
# Output: 1
# Explanation: Both the red and the blue area are optimal.
#
# Constraints:
# n == points.length
# 	2 <= n <= 105
# 	points[i].length == 2
# 	0 <= xi, yi <= 109
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxWidthOfVerticalArea(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        # Extract the x-coordinates and sort them
        x_coords = sorted(point[0] for point in points)

        max_width = 0
        # Iterate through the sorted x-coordinates and find the maximum gap
        for i in range(1, len(x_coords)):
            max_width = max(max_width, x_coords[i] - x_coords[i - 1])

        return max_width