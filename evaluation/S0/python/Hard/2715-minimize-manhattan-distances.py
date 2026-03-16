# Source: https://leetcode.com/problems/minimize-manhattan-distances/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array points representing integer coordinates of some points on a 2D plane, where points[i] = [xi, yi].
#
# The distance between two points is defined as their Manhattan distance.
#
# Return the minimum possible value for maximum distance between any two points by removing exactly one point.
#
# Example:
# Input: points = [[3,10],[5,15],[10,2],[4,4]]
#
# Output: 12
#
# Explanation:
#
# The maximum distance after removing each point is the following:
#
#
# 	After removing the 0th point the maximum distance is between points (5, 15) and (10, 2), which is |5 - 10| + |15 - 2| = 18.
# 	After removing the 1st point the maximum distance is between points (3, 10) and (10, 2), which is |3 - 10| + |10 - 2| = 15.
# 	After removing the 2nd point the maximum distance is between points (5, 15) and (4, 4), which is |5 - 4| + |15 - 4| = 12.
# 	After removing the 3rd point the maximum distance is between points (5, 15) and (10, 2), which is |5 - 10| + |15 - 2| = 18.
#
#
# 12 is the minimum possible maximum distance between any two points after removing exactly one point.
#
# Constraints:
# 3 <= points.length <= 105
# 	points[i].length == 2
# 	1 <= points[i][0], points[i][1] <= 108
#

class Solution(object):
    def minimumDistance(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        n = len(points)
        if n <= 3:
            return 0

        xs = sorted([x for x, y in points])
        ys = sorted([y for x, y in points])

        def manhattan_dist(p1, p2):
            return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])

        def max_distance_excluding(index):
            filtered_points = points[:index] + points[index+1:]
            max_dist = 0
            for i in range(len(filtered_points)):
                for j in range(i + 1, len(filtered_points)):
                    dist = manhattan_dist(filtered_points[i], filtered_points[j])
                    max_dist = max(max_dist, dist)
            return max_dist

        min_max_dist = float('inf')
        for i in range(n):
            current_max_dist = max_distance_excluding(i)
            min_max_dist = min(min_max_dist, current_max_dist)

        return min_max_dist