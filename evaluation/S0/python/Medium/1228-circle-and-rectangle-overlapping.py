# Source: https://leetcode.com/problems/circle-and-rectangle-overlapping/   |   Difficulty: Medium
#
# Problem Description:
# You are given a circle represented as (radius, xCenter, yCenter) and an axis-aligned rectangle represented as (x1, y1, x2, y2), where (x1, y1) are the coordinates of the bottom-left corner, and (x2, y2) are the coordinates of the top-right corner of the rectangle.
#
# Return true if the circle and rectangle are overlapped otherwise return false. In other words, check if there is any point (xi, yi) that belongs to the circle and the rectangle at the same time.
#
# Example:
# Input: radius = 1, xCenter = 0, yCenter = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1
# Output: true
# Explanation: Circle and rectangle share the point (1,0).
#
# Constraints:
# 1 <= radius <= 2000
# 	-104 <= xCenter, yCenter <= 104
# 	-104 <= x1 < x2 <= 104
# 	-104 <= y1 < y2 <= 104
#

class Solution(object):
    def checkOverlap(self, radius, xCenter, yCenter, x1, y1, x2, y2):
        """
        :type radius: int
        :type xCenter: int
        :type yCenter: int
        :type x1: int
        :type y1: int
        :type x2: int
        :type y2: int
        :rtype: bool
        """
        # Find the closest point on the rectangle to the circle's center
        closestX = max(x1, min(xCenter, x2))
        closestY = max(y1, min(yCenter, y2))
        
        # Calculate the distance between the circle's center and this closest point
        distanceX = xCenter - closestX
        distanceY = yCenter - closestY
        
        # If the distance is less than or equal to the radius, they overlap
        return (distanceX ** 2 + distanceY ** 2) <= (radius ** 2)