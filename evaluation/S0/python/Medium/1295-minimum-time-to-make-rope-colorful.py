# Source: https://leetcode.com/problems/minimum-time-to-make-rope-colorful/   |   Difficulty: Medium
#
# Problem Description:
# Alice has n balloons arranged on a rope. You are given a 0-indexed string colors where colors[i] is the color of the ith balloon.
#
# Alice wants the rope to be colorful. She does not want two consecutive balloons to be of the same color, so she asks Bob for help. Bob can remove some balloons from the rope to make it colorful. You are given a 0-indexed integer array neededTime where neededTime[i] is the time (in seconds) that Bob needs to remove the ith balloon from the rope.
#
# Return the minimum time Bob needs to make the rope colorful.
#
# Example:
# Input: colors = "abaac", neededTime = [1,2,3,4,5]
# Output: 3
# Explanation: In the above image, 'a' is blue, 'b' is red, and 'c' is green.
# Bob can remove the blue balloon at index 2. This takes 3 seconds.
# There are no longer two consecutive balloons of the same color. Total time = 3.
#
# Constraints:
# n == colors.length == neededTime.length
# 	1 <= n <= 105
# 	1 <= neededTime[i] <= 104
# 	colors contains only lowercase English letters.
#

class Solution(object):
    def minCost(self, colors, neededTime):
        """
        :type colors: str
        :type neededTime: List[int]
        :rtype: int
        """
        total_time = 0
        max_time = 0
        n = len(colors)
        
        for i in range(n):
            if i > 0 and colors[i] == colors[i - 1]:
                total_time += min(max_time, neededTime[i])
                max_time = max(max_time, neededTime[i])
            else:
                max_time = neededTime[i]
        
        return total_time