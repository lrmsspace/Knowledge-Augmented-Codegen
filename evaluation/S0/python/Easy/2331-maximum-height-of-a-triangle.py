# Source: https://leetcode.com/problems/maximum-height-of-a-triangle/   |   Difficulty: Easy
#
# Problem Description:
# You are given two integers red and blue representing the count of red and blue colored balls. You have to arrange these balls to form a triangle such that the 1st row will have 1 ball, the 2nd row will have 2 balls, the 3rd row will have 3 balls, and so on.
#
# All the balls in a particular row should be the same color, and adjacent rows should have different colors.
#
# Return the maximum height of the triangle that can be achieved.
#
# Example:
# Input: red = 2, blue = 4
#
# Output: 3
#
# Explanation:
#
#
#
# The only possible arrangement is shown above.
#
# Constraints:
# 1 <= red, blue <= 100
#

class Solution(object):
    def maxHeightOfTriangle(self, red, blue):
        """
        :type red: int
        :type blue: int
        :rtype: int
        """
        height = 0
        total_balls = red + blue
        
        while True:
            height += 1
            balls_needed = (height * (height + 1)) // 2
            
            if balls_needed > total_balls:
                return height - 1
            
            # Check if we can form the triangle with alternating colors
            red_needed = (height + 1) // 2 * ((height + 1) // 2 + height // 2)
            blue_needed = height // 2 * (height // 2 + (height + 1) // 2)
            
            if (red_needed <= red and blue_needed <= blue) or (red_needed <= blue and blue_needed <= red):
                continue
            else:
                return height - 1