# Source: https://leetcode.com/problems/rectangle-area-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D array of axis-aligned rectangles. Each rectangle[i] = [xi1, yi1, xi2, yi2] denotes the ith rectangle where (xi1, yi1) are the coordinates of the bottom-left corner, and (xi2, yi2) are the coordinates of the top-right corner.
#
# Calculate the total area covered by all rectangles in the plane. Any area covered by two or more rectangles should only be counted once.
#
# Return the total area. Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
# Output: 6
# Explanation: A total area of 6 is covered by all three rectangles, as illustrated in the picture.
# From (1,1) to (2,2), the green and red rectangles overlap.
# From (1,0) to (2,3), all three rectangles overlap.
#
# Constraints:
# 1 <= rectangles.length <= 200
# 	rectanges[i].length == 4
# 	0 <= xi1, yi1, xi2, yi2 <= 109
# 	xi1 <= xi2
# 	yi1 <= yi2
# 	All rectangles have non zero area.
#

class Solution(object):
    def rectangleArea(self, rectangles):
        """
        :type rectangles: List[List[int]]
        :rtype: int
        """
        OPEN, CLOSE = 0, 1
        events = []
        for x1, y1, x2, y2 in rectangles:
            events.append((x1, OPEN, y1, y2))
            events.append((x2, CLOSE, y1, y2))
        events.sort()

        def calculate_y_length(active_intervals):
            active_intervals.sort()
            total = 0
            current_start, current_end = -1, -1
            for start, end in active_intervals:
                if start > current_end:
                    total += current_end - current_start
                    current_start, current_end = start, end
                else:
                    current_end = max(current_end, end)
            total += current_end - current_start
            return total

        active_intervals = []
        prev_x = events[0][0]
        area = 0
        MOD = 10**9 + 7

        for x, typ, y1, y2 in events:
            y_length = calculate_y_length(active_intervals)
            area += y_length * (x - prev_x)
            area %= MOD

            if typ == OPEN:
                active_intervals.append((y1, y2))
            else:
                active_intervals.remove((y1, y2))

            prev_x = x

        return area % MOD