# Source: https://leetcode.com/problems/minimum-time-difference/   |   Difficulty: Medium
#
# Problem Description:
# Given a list of 24-hour clock time points in "HH:MM" format, return the minimum minutes difference between any two time-points in the list.
#
# Example:
# Input: timePoints = ["23:59","00:00"]
# Output: 1
#
# Constraints:
# 2 <= timePoints.length <= 2 * 104
# 	timePoints[i] is in the format "HH:MM".
#

class Solution(object):
    def findMinDifference(self, timePoints):
        """
        :type timePoints: List[str]
        :rtype: int
        """
        minutes = []
        for time in timePoints:
            h, m = map(int, time.split(':'))
            total_minutes = h * 60 + m
            minutes.append(total_minutes)
        
        minutes.sort()
        min_diff = float('inf')
        
        for i in range(1, len(minutes)):
            diff = minutes[i] - minutes[i - 1]
            min_diff = min(min_diff, diff)
        
        # Check the difference between the last and first time point (across midnight)
        midnight_diff = (minutes[0] + 1440) - minutes[-1]
        min_diff = min(min_diff, midnight_diff)
        
        return min_diff