# Source: https://leetcode.com/problems/largest-rectangle-in-histogram/   |   Difficulty: Hard
#
# Problem Description:
# Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.
#
# Example:
# Input: heights = [2,1,5,6,2,3]
# Output: 10
# Explanation: The above is a histogram where width of each bar is 1.
# The largest rectangle is shown in the red area, which has an area = 10 units.
#
# Constraints:
# 1 <= heights.length <= 105
# 	0 <= heights[i] <= 104
#

class Solution(object):
    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        stack = []
        max_area = 0
        heights.append(0)  # Append a sentinel value to pop all elements at the end

        for i in range(len(heights)):
            while stack and heights[i] < heights[stack[-1]]:
                h = heights[stack.pop()]
                w = i if not stack else i - stack[-1] - 1
                max_area = max(max_area, h * w)
            stack.append(i)

        return max_area