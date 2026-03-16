# Source: https://leetcode.com/problems/valid-boomerang/   |   Difficulty: Easy
#
# Problem Description:
# Given an array points where points[i] = [xi, yi] represents a point on the X-Y plane, return true if these points are a boomerang.
#
# A boomerang is a set of three points that are all distinct and not in a straight line.
#
# Example:
# Input: points = [[1,1],[2,3],[3,2]]
# Output: true
#
# Constraints:
# points.length == 3
# 	points[i].length == 2
# 	0 <= xi, yi <= 100
#

class Solution(object):
    def isBoomerang(self, points):
        """
        :type points: List[List[int]]
        :rtype: bool
        """
        (x1, y1), (x2, y2), (x3, y3) = points
        return (x1 - x2) * (y2 - y3) != (y1 - y2) * (x2 - x3)