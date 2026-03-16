# Source: https://leetcode.com/problems/perfect-rectangle/   |   Difficulty: Hard
#
# Problem Description:
# Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).
#
# Return true if all the rectangles together form an exact cover of a rectangular region.
#
# Example:
# Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
# Output: true
# Explanation: All 5 rectangles together form an exact cover of a rectangular region.
#
# Constraints:
# 1 <= rectangles.length <= 2 * 104
# 	rectangles[i].length == 4
# 	-105 <= xi < ai <= 105
# 	-105 <= yi < bi <= 105
#

class Solution(object):
    def isRectangleCover(self, rectangles):
        """
        :type rectangles: List[List[int]]
        :rtype: bool
        """
        area = 0
        corner_count = {}
        
        min_x = min_y = float('inf')
        max_x = max_y = float('-inf')
        
        for x1, y1, x2, y2 in rectangles:
            area += (x2 - x1) * (y2 - y1)
            
            min_x = min(min_x, x1)
            min_y = min(min_y, y1)
            max_x = max(max_x, x2)
            max_y = max(max_y, y2)
            
            for corner in [(x1, y1), (x1, y2), (x2, y1), (x2, y2)]:
                if corner in corner_count:
                    corner_count[corner] += 1
                else:
                    corner_count[corner] = 1
        
        expected_area = (max_x - min_x) * (max_y - min_y)
        if area != expected_area:
            return False
        
        expected_corners = {(min_x, min_y), (min_x, max_y), (max_x, min_y), (max_x, max_y)}
        
        for corner, count in corner_count.items():
            if corner in expected_corners:
                if count != 1:
                    return False
                expected_corners.remove(corner)
            else:
                if count % 2 != 0:
                    return False
        
        return len(expected_corners) == 0