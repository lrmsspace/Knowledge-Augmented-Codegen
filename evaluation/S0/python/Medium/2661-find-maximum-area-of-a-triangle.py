# Source: https://leetcode.com/problems/find-maximum-area-of-a-triangle/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D array coords of size n x 2, representing the coordinates of n points in an infinite Cartesian plane.
#
# Find twice the maximum area of a triangle with its corners at any three elements from coords, such that at least one side of this triangle is parallel to the x-axis or y-axis. Formally, if the maximum area of such a triangle is A, return 2 * A.
#
# If no such triangle exists, return -1.
#
# Note that a triangle cannot have zero area.
#
# Example:
# Input: coords = [[1,1],[1,2],[3,2],[3,3]]
#
# Output: 2
#
# Explanation:
#
#
#
# The triangle shown in the image has a base 1 and height 2. Hence its area is 1/2 * base * height = 1.
#
# Constraints:
# 1 <= n == coords.length <= 105
# 	1 <= coords[i][0], coords[i][1] <= 106
# 	All coords[i] are unique.
#

class Solution(object):
    def maxArea(self, coords):
        """
        :type coords: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict

        x_map = defaultdict(list)
        y_map = defaultdict(list)

        for x, y in coords:
            x_map[x].append(y)
            y_map[y].append(x)

        max_area = -1

        for x, y_list in x_map.items():
            y_list.sort()
            for i in range(len(y_list)):
                for j in range(i + 1, len(y_list)):
                    y1, y2 = y_list[i], y_list[j]
                    height = abs(y2 - y1)

                    if y1 in y_map and y2 in y_map:
                        x_candidates1 = y_map[y1]
                        x_candidates2 = y_map[y2]

                        for x1 in x_candidates1:
                            if x1 != x:
                                base = abs(x1 - x)
                                area = base * height
                                max_area = max(max_area, area)

                        for x2 in x_candidates2:
                            if x2 != x:
                                base = abs(x2 - x)
                                area = base * height
                                max_area = max(max_area, area)

        return max_area