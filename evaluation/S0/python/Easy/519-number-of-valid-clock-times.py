# Source: https://leetcode.com/problems/number-of-valid-clock-times/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string of length 5 called time, representing the current time on a digital clock in the format "hh:mm". The earliest possible time is "00:00" and the latest possible time is "23:59".
#
# In the string time, the digits represented by the ? symbol are unknown, and must be replaced with a digit from 0 to 9.
#
# Return an integer answer, the number of valid clock times that can be created by replacing every ? with a digit from 0 to 9.
#
# Example:
# Input: time = "?5:00"
# Output: 2
# Explanation: We can replace the ? with either a 0 or 1, producing "05:00" or "15:00". Note that we cannot replace it with a 2, since the time "25:00" is invalid. In total, we have two choices.
#
# Constraints:
# time is a valid string of length 5 in the format "hh:mm".
# 	"00" <= hh <= "23"
# 	"00" <= mm <= "59"
# 	Some of the digits might be replaced with '?' and need to be replaced with digits from 0 to 9.
#

class Solution(object):
    def countTime(self, time):
        """
        :type time: str
        :rtype: int
        """
        h1, h2, m1, m2 = time[0], time[1], time[3], time[4]
        
        # Calculate possibilities for hours
        if h1 == '?' and h2 == '?':
            hour_possibilities = 24
        elif h1 == '?':
            hour_possibilities = 3 if h2 <= '3' else 2
        elif h2 == '?':
            hour_possibilities = 10 if h1 <= '1' else 4
        else:
            hour_possibilities = 1
        
        # Calculate possibilities for minutes
        if m1 == '?' and m2 == '?':
            minute_possibilities = 60
        elif m1 == '?':
            minute_possibilities = 6
        elif m2 == '?':
            minute_possibilities = 10
        else:
            minute_possibilities = 1
        
        return hour_possibilities * minute_possibilities