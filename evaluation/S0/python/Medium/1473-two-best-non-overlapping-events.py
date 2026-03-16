# Source: https://leetcode.com/problems/two-best-non-overlapping-events/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed 2D integer array of events where events[i] = [startTimei, endTimei, valuei]. The ith event starts at startTimei and ends at endTimei, and if you attend this event, you will receive a value of valuei. You can choose at most two non-overlapping events to attend such that the sum of their values is maximized.
#
# Return this maximum sum.
#
# Note that the start time and end time is inclusive: that is, you cannot attend two events where one of them starts and the other ends at the same time. More specifically, if you attend an event with end time t, the next event must start at or after t + 1.
#
# Example:
# Input: events = [[1,3,2],[4,5,2],[2,4,3]]
# Output: 4
# Explanation: Choose the green events, 0 and 1 for a sum of 2 + 2 = 4.
#
# Constraints:
# 2 <= events.length <= 105
# 	events[i].length == 3
# 	1 <= startTimei <= endTimei <= 109
# 	1 <= valuei <= 106
#

class Solution(object):
    def maxTwoEvents(self, events):
        """
        :type events: List[List[int]]
        :rtype: int
        """
        events.sort()
        n = len(events)
        max_value_from_right = [0] * (n + 1)
        
        for i in range(n - 1, -1, -1):
            max_value_from_right[i] = max(max_value_from_right[i + 1], events[i][2])
        
        max_sum = 0
        
        for i in range(n):
            start, end, value = events[i]
            max_sum = max(max_sum, value)
            
            left, right = i + 1, n - 1
            idx = n
            
            while left <= right:
                mid = (left + right) // 2
                if events[mid][0] > end:
                    idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            
            if idx < n:
                max_sum = max(max_sum, value + max_value_from_right[idx])
        
        return max_sum