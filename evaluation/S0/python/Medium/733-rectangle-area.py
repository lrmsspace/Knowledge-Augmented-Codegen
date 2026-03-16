# Source: https://leetcode.com/problems/rectangle-area/   |   Difficulty: Medium
#
# Problem Description:
# Given the coordinates of two rectilinear rectangles in a 2D plane, return the total area covered by the two rectangles.
#
# The first rectangle is defined by its bottom-left corner (ax1, ay1) and its top-right corner (ax2, ay2).
#
# The second rectangle is defined by its bottom-left corner (bx1, by1) and its top-right corner (bx2, by2).
#
# Example:
# Input: ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4, bx1 = 0, by1 = -1, bx2 = 9, by2 = 2
# Output: 45
#
# Constraints:
# -104 <= ax1 <= ax2 <= 104
# 	-104 <= ay1 <= ay2 <= 104
# 	-104 <= bx1 <= bx2 <= 104
# 	-104 <= by1 <= by2 <= 104
#

class Solution(object):
    def computeArea(self, ax1, ay1, ax2, ay2, bx1, by1, bx2, by2):
        """
        :type ax1: int
        :type ay1: int
        :type ax2: int
        :type ay2: int
        :type bx1: int
        :type by1: int
        :type bx2: int
        :type by2: int
        :rtype: int
        """
        # Calculate the area of both rectangles
        area1 = (ax2 - ax1) * (ay2 - ay1)
        area2 = (bx2 - bx1) * (by2 - by1)

        # Calculate the overlap area
        overlap_width = max(0, min(ax2, bx2) - max(ax1, bx1))
        overlap_height = max(0, min(ay2, by2) - max(ay1, by1))
        overlap_area = overlap_width * overlap_height

        # Total area is the sum of both areas minus the overlap area
        total_area = area1 + area2 - overlap_area

        return total_area