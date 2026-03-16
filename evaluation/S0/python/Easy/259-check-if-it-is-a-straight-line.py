# Source: https://leetcode.com/problems/check-if-it-is-a-straight-line/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array coordinates, coordinates[i] = [x, y], where [x, y] represents the coordinate of a point. Check if these points make a straight line in the XY plane.
#
# Example:
# Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
# Output: true
#
# Constraints:
# 2 <= coordinates.length <= 1000
# 	coordinates[i].length == 2
# 	-10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
# 	coordinates contains no duplicate point.
#

class Solution(object):
    def checkStraightLine(self, coordinates):
        """
        :type coordinates: List[List[int]]
        :rtype: bool
        """
        (x0, y0), (x1, y1) = coordinates[:2]
        for x, y in coordinates[2:]:
            if (y1 - y0) * (x - x0) != (y - y0) * (x1 - x0):
                return False
        return True