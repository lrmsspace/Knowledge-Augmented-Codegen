# Source: https://leetcode.com/problems/remove-covered-intervals/   |   Difficulty: Medium
#
# Problem Description:
# Given an array intervals where intervals[i] = [li, ri] represent the interval [li, ri), remove all intervals that are covered by another interval in the list.
#
# The interval [a, b) is covered by the interval [c, d) if and only if c <= a and b <= d.
#
# Return the number of remaining intervals.
#
# Example:
# Input: intervals = [[1,4],[3,6],[2,8]]
# Output: 2
# Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
#
# Constraints:
# 1 <= intervals.length <= 1000
# 	intervals[i].length == 2
# 	0 <= li < ri <= 105
# 	All the given intervals are unique.
#

class Solution(object):
    def removeCoveredIntervals(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: int
        """
        intervals.sort(key=lambda x: (x[0], -x[1]))
        count = 0
        end = 0

        for interval in intervals:
            if interval[1] > end:
                count += 1
                end = interval[1]

        return count