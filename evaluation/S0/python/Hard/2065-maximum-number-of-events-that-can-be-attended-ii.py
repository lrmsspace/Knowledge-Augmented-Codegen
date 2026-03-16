# Source: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of events where events[i] = [startDayi, endDayi, valuei]. The ith event starts at startDayi and ends at endDayi, and if you attend this event, you will receive a value of valuei. You are also given an integer k which represents the maximum number of events you can attend.
#
# You can only attend one event at a time. If you choose to attend an event, you must attend the entire event. Note that the end day is inclusive: that is, you cannot attend two events where one of them starts and the other ends on the same day.
#
# Return the maximum sum of values that you can receive by attending events.
#
# Example:
# Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
# Output: 7
# Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.
#
# Constraints:
# 1 <= k <= events.length
# 	1 <= k * events.length <= 106
# 	1 <= startDayi <= endDayi <= 109
# 	1 <= valuei <= 106
#

class Solution(object):
    def maxValue(self, events, k):
        """
        :type events: List[List[int]]
        :type k: int
        :rtype: int
        """
        import bisect
        events.sort()
        n = len(events)
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        start_days = [event[0] for event in events]

        for i in range(n - 1, -1, -1):
            for j in range(1, k + 1):
                next_index = bisect.bisect_right(start_days, events[i][1])
                dp[i][j] = max(dp[i + 1][j], events[i][2] + dp[next_index][j - 1])

        return dp[0][k]