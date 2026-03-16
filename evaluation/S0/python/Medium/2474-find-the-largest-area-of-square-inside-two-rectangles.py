# Source: https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/   |   Difficulty: Medium
#
# Problem Description:
# There exist n rectangles in a 2D plane with edges parallel to the x and y axis. You are given two 2D integer arrays bottomLeft and topRight where bottomLeft[i] = [a_i, b_i] and topRight[i] = [c_i, d_i] represent the bottom-left and top-right coordinates of the ith rectangle, respectively.
#
# You need to find the maximum area of a square that can fit inside the intersecting region of at least two rectangles. Return 0 if such a square does not exist.
#
# Example:
# Input: bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]
#
# Output: 1
#
# Explanation:
#
# A square with side length 1 can fit inside either the intersecting region of rectangles 0 and 1 or the intersecting region of rectangles 1 and 2. Hence the maximum area is 1. It can be shown that a square with a greater side length can not fit inside any intersecting region of two rectangles.
#
# Constraints:
# n == bottomLeft.length == topRight.length
# 	2 <= n <= 103
# 	bottomLeft[i].length == topRight[i].length == 2
# 	1 <= bottomLeft[i][0], bottomLeft[i][1] <= 107
# 	1 <= topRight[i][0], topRight[i][1] <= 107
# 	bottomLeft[i][0] < topRight[i][0]
# 	bottomLeft[i][1] < topRight[i][1]
#

class Solution(object):
    def largestSquareArea(self, bottomLeft, topRight):
        """
        :type bottomLeft: List[List[int]]
        :type topRight: List[List[int]]
        :rtype: int
        """
        events = []
        for (x1, y1), (x2, y2) in zip(bottomLeft, topRight):
            events.append((x1, y1, y2, 1))  # rectangle starts
            events.append((x2, y1, y2, -1)) # rectangle ends

        events.sort()
        active_intervals = []
        max_area = 0

        def calculate_max_square():
            nonlocal max_area
            active_intervals.sort()
            merged = []
            for start, end in active_intervals:
                if not merged or merged[-1][1] < start:
                    merged.append([start, end])
                else:
                    merged[-1][1] = max(merged[-1][1], end)

            for i in range(len(merged)):
                for j in range(i + 1, len(merged)):
                    overlap_start = max(merged[i][0], merged[j][0])
                    overlap_end = min(merged[i][1], merged[j][1])
                    if overlap_start < overlap_end:
                        side_length = overlap_end - overlap_start
                        max_area = max(max_area, side_length * side_length)

        for x, y1, y2, typ in events:
            if typ == 1:
                active_intervals.append((y1, y2))
                calculate_max_square()
            else:
                active_intervals.remove((y1, y2))

        return max_area