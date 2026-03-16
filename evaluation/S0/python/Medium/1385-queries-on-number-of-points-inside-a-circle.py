# Source: https://leetcode.com/problems/queries-on-number-of-points-inside-a-circle/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array points where points[i] = [xi, yi] is the coordinates of the ith point on a 2D plane. Multiple points can have the same coordinates.
#
# You are also given an array queries where queries[j] = [xj, yj, rj] describes a circle centered at (xj, yj) with a radius of rj.
#
# For each query queries[j], compute the number of points inside the jth circle. Points on the border of the circle are considered inside.
#
# Return an array answer, where answer[j] is the answer to the jth query.
#
# Example:
# Input: points = [[1,3],[3,3],[5,3],[2,2]], queries = [[2,3,1],[4,3,1],[1,1,2]]
# Output: [3,2,2]
# Explanation: The points and circles are shown above.
# queries[0] is the green circle, queries[1] is the red circle, and queries[2] is the blue circle.
#
# Constraints:
# 1 <= points.length <= 500
# 	points[i].length == 2
# 	0 <= x​​​​​​i, y​​​​​​i <= 500
# 	1 <= queries.length <= 500
# 	queries[j].length == 3
# 	0 <= xj, yj <= 500
# 	1 <= rj <= 500
# 	All coordinates are integers.
#
#
#  
# Follow up: Could you find the answer for each query in better complexity than O(n)?
#

class Solution(object):
    def countPoints(self, points, queries):
        """
        :type points: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        result = []
        for xj, yj, rj in queries:
            count = 0
            rj_squared = rj * rj
            for xi, yi in points:
                dx = xi - xj
                dy = yi - yj
                if dx * dx + dy * dy <= rj_squared:
                    count += 1
            result.append(count)
        return result