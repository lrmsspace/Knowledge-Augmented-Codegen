# Source: https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer eventTime denoting the duration of an event. You are also given two integer arrays startTime and endTime, each of length n.
#
# These represent the start and end times of n non-overlapping meetings that occur during the event between time t = 0 and time t = eventTime, where the ith meeting occurs during the time [startTime[i], endTime[i]].
#
# You can reschedule at most one meeting by moving its start time while maintaining the same duration, such that the meetings remain non-overlapping, to maximize the longest continuous period of free time during the event.
#
# Return the maximum amount of free time possible after rearranging the meetings.
#
# Note that the meetings can not be rescheduled to a time outside the event and they should remain non-overlapping.
#
# Note: In this version, it is valid for the relative ordering of the meetings to change after rescheduling one meeting.
#
# Example:
# Input: eventTime = 5, startTime = [1,3], endTime = [2,5]
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
# 	0 <= startTime[i] < endTime[i] <= eventTime
# 	endTime[i] <= startTime[i + 1] where i lies in the range [0, n - 2].
#

class Solution(object):
    def maxFreeTime(self, eventTime, startTime, endTime):
        """
        :type eventTime: int
        :type startTime: List[int]
        :type endTime: List[int]
        :rtype: int
        """
        n = len(startTime)
        max_free = 0

        # Calculate initial free times
        free_times = []
        prev_end = 0
        for i in range(n):
            free_times.append(startTime[i] - prev_end)
            prev_end = endTime[i]
        free_times.append(eventTime - prev_end)

        max_free = max(free_times)

        # Try rescheduling each meeting
        for i in range(n):
            duration = endTime[i] - startTime[i]

            # Check moving meeting to the start
            if i == 0:
                new_free = startTime[0] + (free_times[1] if n > 1 else eventTime - endTime[0])
            else:
                new_free = free_times[i - 1] + (free_times[i + 1] if i + 1 < n else eventTime - endTime[i])

            max_free = max(max_free, new_free)

            # Check moving meeting to the end
            if i == n - 1:
                new_free = (free_times[n - 2] if n > 1 else startTime[0]) + (eventTime - endTime[n - 1])
            else:
                new_free = (free_times[i - 1] if i > 0 else startTime[0]) + free_times[i + 1]

            max_free = max(max_free, new_free)

        return max_free