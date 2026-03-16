# Source: https://leetcode.com/problems/angle-between-hands-of-a-clock/   |   Difficulty: Medium
#
# Problem Description:
# Given two numbers, hour and minutes, return the smaller angle (in degrees) formed between the hour and the minute hand.
#
# Answers within 10-5 of the actual value will be accepted as correct.
#
# Example:
# Input: hour = 12, minutes = 30
# Output: 165
#
# Constraints:
# 1 <= hour <= 12
# 	0 <= minutes <= 59
#

class Solution(object):
    def angleClock(self, hour, minutes):
        """
        :type hour: int
        :type minutes: int
        :rtype: float
        """
        minute_angle = minutes * 6
        hour_angle = (hour % 12) * 30 + (minutes / 60) * 30
        angle = abs(hour_angle - minute_angle)
        return min(angle, 360 - angle)