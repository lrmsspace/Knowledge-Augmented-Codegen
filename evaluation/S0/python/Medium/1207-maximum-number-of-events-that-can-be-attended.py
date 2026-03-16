# Source: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of events where events[i] = [startDayi, endDayi]. Every event i starts at startDayi and ends at endDayi.
#
# You can attend an event i at any day d where startDayi <= d <= endDayi. You can only attend one event at any time d.
#
# Return the maximum number of events you can attend.
#
# Example:
# Input: events = [[1,2],[2,3],[3,4]]
# Output: 3
# Explanation: You can attend all the three events.
# One way to attend them all is as shown.
# Attend the first event on day 1.
# Attend the second event on day 2.
# Attend the third event on day 3.
#
# Constraints:
# 1 <= events.length <= 105
# 	events[i].length == 2
# 	1 <= startDayi <= endDayi <= 105
#

class Solution(object):
    def maxEvents(self, events):
        """
        :type events: List[List[int]]
        :rtype: int
        """
        events.sort()
        import heapq
        min_heap = []
        day = 0
        event_index = 0
        attended_events = 0
        total_events = len(events)

        while event_index < total_events or min_heap:
            if not min_heap:
                day = events[event_index][0]

            while event_index < total_events and events[event_index][0] <= day:
                heapq.heappush(min_heap, events[event_index][1])
                event_index += 1

            heapq.heappop(min_heap)
            attended_events += 1
            day += 1

            while min_heap and min_heap[0] < day:
                heapq.heappop(min_heap)

        return attended_events