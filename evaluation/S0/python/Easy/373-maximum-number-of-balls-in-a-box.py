# Source: https://leetcode.com/problems/maximum-number-of-balls-in-a-box/   |   Difficulty: Easy
#
# Problem Description:
# You are working in a ball factory where you have n balls numbered from lowLimit up to highLimit inclusive (i.e., n == highLimit - lowLimit + 1), and an infinite number of boxes numbered from 1 to infinity.
#
# Your job at this factory is to put each ball in the box with a number equal to the sum of digits of the ball's number. For example, the ball number 321 will be put in the box number 3 + 2 + 1 = 6 and the ball number 10 will be put in the box number 1 + 0 = 1.
#
# Given two integers lowLimit and highLimit, return the number of balls in the box with the most balls.
#
# Example:
# Input: lowLimit = 1, highLimit = 10
# Output: 2
# Explanation:
# Box Number:  1 2 3 4 5 6 7 8 9 10 11 ...
# Ball Count:  2 1 1 1 1 1 1 1 1 0  0  ...
# Box 1 has the most number of balls with 2 balls.
#
# Constraints:
# 1 <= lowLimit <= highLimit <= 105
#

class Solution(object):
    def countBalls(self, lowLimit, highLimit):
        """
        :type lowLimit: int
        :type highLimit: int
        :rtype: int
        """
        box_counts = {}
        
        for ball_number in range(lowLimit, highLimit + 1):
            box_number = sum(int(digit) for digit in str(ball_number))
            if box_number in box_counts:
                box_counts[box_number] += 1
            else:
                box_counts[box_number] = 1
        
        return max(box_counts.values())