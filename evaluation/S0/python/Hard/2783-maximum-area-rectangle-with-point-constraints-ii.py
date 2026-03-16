# Source: https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-ii/   |   Difficulty: Hard
#
# Problem Description:
# There are n points on an infinite plane. You are given two integer arrays xCoord and yCoord where (xCoord[i], yCoord[i]) represents the coordinates of the ith point.
#
# Your task is to find the maximum area of a rectangle that:
#
#
# 	Can be formed using four of these points as its corners.
# 	Does not contain any other point inside or on its border.
# 	Has its edges parallel to the axes.
#
#
# Return the maximum area that you can obtain or -1 if no such rectangle is possible.
#
# Example:
# Input: xCoord = [1,1,3,3], yCoord = [1,3,1,3]
#
# Output: 4
#
# Explanation:
#
#
#
# We can make a rectangle with these 4 points as corners and there is no other point that lies inside or on the border. Hence, the maximum possible area would be 4.
#
# Constraints:
# 1 <= xCoord.length == yCoord.length <= 2 * 105
# 	0 <= xCoord[i], yCoord[i] <= 8 * 107
# 	All the given points are unique.
#

class Solution(object):
    def maxRectangleArea(self, xCoord, yCoord):
        """
        :type xCoord: List[int]
        :type yCoord: List[int]
        :rtype: int
        """
        points = set(zip(xCoord, yCoord))
        n = len(xCoord)
        max_area = -1

        for i in range(n):
            for j in range(i + 1, n):
                if xCoord[i] != xCoord[j] and yCoord[i] != yCoord[j]:
                    if (xCoord[i], yCoord[j]) in points and (xCoord[j], yCoord[i]) in points:
                        area = abs(xCoord[i] - xCoord[j]) * abs(yCoord[i] - yCoord[j])
                        max_area = max(max_area, area)

        return max_area 