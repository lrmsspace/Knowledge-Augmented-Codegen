# Source: https://leetcode.com/problems/separate-squares-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
#
# Find the minimum y-coordinate value of a horizontal line such that the total area of the squares above the line equals the total area of the squares below the line.
#
# Answers within 10-5 of the actual answer will be accepted.
#
# Note: Squares may overlap. Overlapping areas should be counted multiple times.
#
# Example:
# Input: squares = [[0,0,1],[2,2,1]]
#
# Output: 1.00000
#
# Explanation:
#
#
#
# Any horizontal line between y = 1 and y = 2 will have 1 square unit above it and 1 square unit below it. The lowest option is 1.
#
# Constraints:
# 1 <= squares.length <= 5 * 104
# 	squares[i] = [xi, yi, li]
# 	squares[i].length == 3
# 	0 <= xi, yi <= 109
# 	1 <= li <= 109
# 	The total area of all the squares will not exceed 1012.
#

class Solution(object):
    def separateSquares(self, squares):
        """
        :type squares: List[List[int]]
        :rtype: float
        """
        events = []
        total_area = 0
        
        for x, y, l in squares:
            events.append((y, l * l))        # Square starts
            events.append((y + l, -l * l))   # Square ends
            total_area += l * l
        
        events.sort()
        
        half_area = total_area / 2
        current_area = 0
        prev_y = 0
        
        for y, area_change in events:
            if current_area == half_area:
                return prev_y
            
            if current_area < half_area <= current_area + area_change:
                return prev_y + (half_area - current_area) / (area_change / (y - prev_y))
            
            current_area += area_change
            prev_y = y
        
        return prev_y