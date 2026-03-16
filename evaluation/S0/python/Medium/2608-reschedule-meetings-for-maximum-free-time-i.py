# Source: https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer eventTime denoting the duration of an event, where the event occurs from time t = 0 to time t = eventTime.
#
# You are also given two integer arrays startTime and endTime, each of length n. These represent the start and end time of n non-overlapping meetings, where the ith meeting occurs during the time [startTime[i], endTime[i]].
#
# You can reschedule at most k meetings by moving their start time while maintaining the same duration, to maximize the longest continuous period of free time during the event.
#
# The relative order of all the meetings should stay the same and they should remain non-overlapping.
#
# Return the maximum amount of free time possible after rearranging the meetings.
#
# Note that the meetings can not be rescheduled to a time outside the event.
#
# Example:
# Input: eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]
#
# Output: 2
#
# Explanation:
#
#
#
# Reschedule the meeting at [1, 2] to [2, 3], leaving no meetings during the time [0, 2].
#
# Constraints:
# 1 <= eventTime <= 109
# 	n == startTime.length == endTime.length
# 	2 <= n <= 105
# 	1 <= k <= n
# 	0 <= startTime[i] < endTime[i] <= eventTime
# 	endTime[i] <= startTime[i + 1] where i lies in the range [0, n - 2].
#

class Solution(object):
    def maxFreeTime(self, eventTime, k, startTime, endTime):
        """
        :type eventTime: int
        :type k: int
        :type startTime: List[int]
        :type endTime: List[int]
        :rtype: int
        """
        n = len(startTime)
        gaps = [startTime[0]] + [startTime[i] - endTime[i - 1] for i in range(1, n)] + [eventTime - endTime[-1]]
        total_gaps = sum(gaps)
        
        if k >= n:
            return total_gaps
        
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        
        for i in range(1, n + 1):
            gap = gaps[i]
            for j in range(k + 1):
                dp[i][j] = dp[i - 1][j] + gap
                if j > 0:
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1])
        
        return max(dp[n])