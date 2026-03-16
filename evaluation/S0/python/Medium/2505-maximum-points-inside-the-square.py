# Source: https://leetcode.com/problems/maximum-points-inside-the-square/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D array points and a string s where, points[i] represents the coordinates of point i, and s[i] represents the tag of point i.
#
# A valid square is a square centered at the origin (0, 0), has edges parallel to the axes, and does not contain two points with the same tag.
#
# Return the maximum number of points contained in a valid square.
#
# Note:
#
#
# 	A point is considered to be inside the square if it lies on or within the square's boundaries.
# 	The side length of the square can be zero.
#
# Example:
# Input: points = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], s = "abdca"
#
# Output: 2
#
# Explanation:
#
# The square of side length 4 covers two points points[0] and points[1].
#
# Constraints:
# 1 <= s.length, points.length <= 105
# 	points[i].length == 2
# 	-109 <= points[i][0], points[i][1] <= 109
# 	s.length == points.length
# 	points consists of distinct coordinates.
# 	s consists only of lowercase English letters.
#

class Solution(object):
    def maxPointsInsideSquare(self, points, s):
        """
        :type points: List[List[int]]
        :type s: str
        :rtype: int
        """
        from collections import defaultdict

        tag_to_coords = defaultdict(list)
        for (x, y), tag in zip(points, s):
            tag_to_coords[tag].append((x, y))

        unique_points = []
        for coords in tag_to_coords.values():
            unique_points.append(coords[0])

        def can_fit_square(side_length):
            half_side = side_length / 2
            count = 0
            for x, y in unique_points:
                if -half_side <= x <= half_side and -half_side <= y <= half_side:
                    count += 1
            return count

        left, right = 0, max(max(abs(x), abs(y)) for x, y in unique_points) * 2
        max_points = 0

        while left <= right:
            mid = (left + right) // 2
            points_in_square = can_fit_square(mid)
            max_points = max(max_points, points_in_square)

            if points_in_square > 0:
                left = mid + 1
            else:
                right = mid - 1

        return max_points