# Source: https://leetcode.com/problems/beautiful-towers-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array heights of n integers representing the number of bricks in n consecutive towers. Your task is to remove some bricks to form a mountain-shaped tower arrangement. In this arrangement, the tower heights are non-decreasing, reaching a maximum peak value with one or multiple consecutive towers and then non-increasing.
#
# Return the maximum possible sum of heights of a mountain-shaped tower arrangement.
#
# Example:
# Input: heights = [5,3,4,1,1]
#
# Output: 13
#
# Explanation:
#
# We remove some bricks to make heights = [5,3,3,1,1], the peak is at index 0.
#
# Constraints:
# 1 <= n == heights.length <= 103
# 	1 <= heights[i] <= 109
#

class Solution(object):
    def maximumSumOfHeights(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        n = len(heights)
        
        def calculate_dp(heights):
            dp = [0] * n
            stack = []
            for i in range(n):
                while stack and heights[stack[-1]] > heights[i]:
                    stack.pop()
                if stack:
                    prev_index = stack[-1]
                    dp[i] = dp[prev_index] + heights[i] * (i - prev_index)
                else:
                    dp[i] = heights[i] * (i + 1)
                stack.append(i)
            return dp
        
        left_dp = calculate_dp(heights)
        right_dp = calculate_dp(heights[::-1])[::-1]
        
        max_sum = 0
        for i in range(n):
            total = left_dp[i] + right_dp[i] - heights[i]
            max_sum = max(max_sum, total)
        
        return max_sum