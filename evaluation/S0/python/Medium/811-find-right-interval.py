# Source: https://leetcode.com/problems/find-right-interval/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of intervals, where intervals[i] = [starti, endi] and each starti is unique.
#
# The right interval for an interval i is an interval j such that startj >= endi and startj is minimized. Note that i may equal j.
#
# Return an array of right interval indices for each interval i. If no right interval exists for interval i, then put -1 at index i.
#
# Example:
# Input: intervals = [[1,2]]
# Output: [-1]
# Explanation: There is only one interval in the collection, so it outputs -1.
#
# Constraints:
# 1 <= intervals.length <= 2 * 104
# 	intervals[i].length == 2
# 	-106 <= starti <= endi <= 106
# 	The start point of each interval is unique.
#

class Solution(object):
    def findRightInterval(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: List[int]
        """
        import bisect

        starts = sorted((interval[0], i) for i, interval in enumerate(intervals))
        result = []

        for interval in intervals:
            end = interval[1]
            idx = bisect.bisect_left(starts, (end,))

            if idx < len(starts):
                result.append(starts[idx][1])
            else:
                result.append(-1)

        return result