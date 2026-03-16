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

class Solution(object):
    def maxWidthOfVerticalArea(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        xs = sorted([p[0] for p in points])
        return max(xs[i] - xs[i-1] for i in range(1, len(xs)))