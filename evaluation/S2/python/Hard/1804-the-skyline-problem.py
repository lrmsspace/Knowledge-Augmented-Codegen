# Source: https://leetcode.com/problems/the-skyline-problem/   |   Difficulty: Hard
#
# Problem Description:
# A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return the skyline formed by these buildings collectively.
#
# The geometric information of each building is given in the array buildings where buildings[i] = [lefti, righti, heighti]:
#
#
# 	lefti is the x coordinate of the left edge of the ith building.
# 	righti is the x coordinate of the right edge of the ith building.
# 	heighti is the height of the ith building.
#
#
# You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.
#
# The skyline should be represented as a list of "key points" sorted by their x-coordinate in the form [[x1,y1],[x2,y2],...]. Each key point is the left endpoint of some horizontal segment in the skyline except the last point in the list, which always has a y-coordinate 0 and is used to mark the skyline's termination where the rightmost building ends. Any ground between the leftmost and rightmost buildings should be part of the skyline's contour.
#
# Note: There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...,[2 3],[4 5],[12 7],...]
#
# Example:
# Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
# Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
# Explanation:
# Figure A shows the buildings of the input.
# Figure B shows the skyline formed by those buildings. The red points in figure B represent the key points in the output list.
#
# Constraints:
# 1 <= buildings.length <= 104
# 	0 <= lefti < righti <= 231 - 1
# 	1 <= heighti <= 231 - 1
# 	buildings is sorted by lefti in non-decreasing order.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getSkyline(self, buildings):
        """
        :type buildings: List[List[int]]
        :rtype: List[List[int]]
        """
        
        # Step 1: Create a list of "events" for building start and end
        events = []
        for left, right, height in buildings:
            events.append((left, -height))  # Building start
            events.append((right, height))  # Building end
        
        # Step 2: Sort the events
        events.sort(key=lambda x: (x[0], x[1]))
        
        # Step 3: Use a max heap to keep track of active building heights
        import heapq
        result = []
        active_heights = [0]  # Max heap (using negative heights)
        prev_x = 0
        prev_max_height = 0
        
        for x, h in events:
            if h < 0:  # Start of a building
                heapq.heappush(active_heights, h)
            else:  # End of a building
                active_heights.remove(-h)  # Remove the building height from the heap
                heapq.heapify(active_heights)  # Re-heapify after removal
            
            current_max_height = -active_heights[0]  # Current max height
            
            if current_max_height != prev_max_height:
                result.append([x, current_max_height])
                prev_max_height = current_max_height
        
        return result
        
