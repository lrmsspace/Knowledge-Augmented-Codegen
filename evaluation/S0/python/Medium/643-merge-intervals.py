# Source: https://leetcode.com/problems/merge-intervals/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
#
# Example:
# Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
# Output: [[1,6],[8,10],[15,18]]
# Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
#
# Constraints:
# 1 <= intervals.length <= 104
# 	intervals[i].length == 2
# 	0 <= starti <= endi <= 104
#

class Solution(object):
    def merge(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: List[List[int]]
        """
        if not intervals:
            return []
        
        # Sort the intervals based on the start time
        intervals.sort(key=lambda x: x[0])
        
        merged = []
        for interval in intervals:
            # If merged is empty or there is no overlap, add the interval
            if not merged or merged[-1][1] < interval[0]:
                merged.append(interval)
            else:
                # There is an overlap, so we merge the current interval
                merged[-1][1] = max(merged[-1][1], interval[1])
        
        return merged