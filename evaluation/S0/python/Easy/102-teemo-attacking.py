# Source: https://leetcode.com/problems/teemo-attacking/   |   Difficulty: Easy
#
# Problem Description:
# Our hero Teemo is attacking an enemy Ashe with poison attacks! When Teemo attacks Ashe, Ashe gets poisoned for a exactly duration seconds. More formally, an attack at second t will mean Ashe is poisoned during the inclusive time interval [t, t + duration - 1]. If Teemo attacks again before the poison effect ends, the timer for it is reset, and the poison effect will end duration seconds after the new attack.
#
# You are given a non-decreasing integer array timeSeries, where timeSeries[i] denotes that Teemo attacks Ashe at second timeSeries[i], and an integer duration.
#
# Return the total number of seconds that Ashe is poisoned.
#
# Example:
# Input: timeSeries = [1,4], duration = 2
# Output: 4
# Explanation: Teemo's attacks on Ashe go as follows:
# - At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
# - At second 4, Teemo attacks, and Ashe is poisoned for seconds 4 and 5.
# Ashe is poisoned for seconds 1, 2, 4, and 5, which is 4 seconds in total.
#
# Constraints:
# 1 <= timeSeries.length <= 104
# 	0 <= timeSeries[i], duration <= 107
# 	timeSeries is sorted in non-decreasing order.
#

class Solution(object):
    def findPoisonedDuration(self, timeSeries, duration):
        """
        :type timeSeries: List[int]
        :type duration: int
        :rtype: int
        """
        total_poisoned_time = 0
        n = len(timeSeries)
        
        for i in range(n - 1):
            # Calculate the time until the next attack
            time_until_next_attack = timeSeries[i + 1] - timeSeries[i]
            # Add the minimum of duration or time until next attack
            total_poisoned_time += min(duration, time_until_next_attack)
        
        # Add the duration for the last attack
        total_poisoned_time += duration
        
        return total_poisoned_time