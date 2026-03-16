# Source: https://leetcode.com/problems/trapping-rain-water/   |   Difficulty: Hard
#
# Problem Description:
# Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
#
# Example:
# Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
# Output: 6
# Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
#
# Constraints:
# n == height.length
# 	1 <= n <= 2 * 104
# 	0 <= height[i] <= 105
#

class Solution(object):
    def trap(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        if not height:
            return 0
        
        left, right = 0, len(height) - 1
        left_max, right_max = height[left], height[right]
        water_trapped = 0
        
        while left < right:
            if left_max < right_max:
                left += 1
                left_max = max(left_max, height[left])
                water_trapped += left_max - height[left]
            else:
                right -= 1
                right_max = max(right_max, height[right])
                water_trapped += right_max - height[right]
        
        return water_trapped