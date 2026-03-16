# Source: https://leetcode.com/problems/separate-squares-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
#
# Find the minimum y-coordinate value of a horizontal line such that the total area covered by squares above the line equals the total area covered by squares below the line.
#
# Answers within 10-5 of the actual answer will be accepted.
#
# Note: Squares may overlap. Overlapping areas should be counted only once in this version.
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
# Any horizontal line between y = 1 and y = 2 results in an equal split, with 1 square unit above and 1 square unit below. The minimum y-value is 1.
#
# Constraints:
# 1 <= squares.length <= 5 * 104
# 	squares[i] = [xi, yi, li]
# 	squares[i].length == 3
# 	0 <= xi, yi <= 109
# 	1 <= li <= 109
# 	The total area of all the squares will not exceed 1015.
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
            events.append((y, x, x + l, 1))      # Square bottom edge
            events.append((y + l, x, x + l, -1)) # Square top edge
            total_area += l * l
        
        events.sort()
        
        def calculate_covered_length(active_intervals):
            active_intervals.sort()
            covered_length = 0
            current_start, current_end = -1, -1
            
            for start, end in active_intervals:
                if start > current_end:
                    covered_length += current_end - current_start
                    current_start, current_end = start, end
                else:
                    current_end = max(current_end, end)
            
            covered_length += current_end - current_start
            return covered_length
        
        prev_y = 0
        area_below = 0
        active_intervals = []
        
        for y, x_start, x_end, typ in events:
            height = y - prev_y
            if height > 0:
                covered_length = calculate_covered_length(active_intervals)
                area_below += covered_length * height
            
            if typ == 1:
                active_intervals.append((x_start, x_end))
            else:
                active_intervals.remove((x_start, x_end))
            
            if area_below * 2 >= total_area:
                remaining_area = total_area / 2 - (area_below - covered_length * height)
                final_y = prev_y + remaining_area / covered_length
                return final_y
            
            prev_y = y
        
        return prev_y