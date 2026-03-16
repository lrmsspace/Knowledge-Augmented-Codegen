# Source: https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D integer array intervals where intervals[i] = [lefti, righti] represents the inclusive interval [lefti, righti].
#
# You have to divide the intervals into one or more groups such that each interval is in exactly one group, and no two intervals that are in the same group intersect each other.
#
# Return the minimum number of groups you need to make.
#
# Two intervals intersect if there is at least one common number between them. For example, the intervals [1, 5] and [5, 8] intersect.
#
# Example:
# Input: intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
# Output: 3
# Explanation: We can divide the intervals into the following groups:
# - Group 1: [1, 5], [6, 8].
# - Group 2: [2, 3], [5, 10].
# - Group 3: [1, 10].
# It can be proven that it is not possible to divide the intervals into fewer than 3 groups.
#
# Constraints:
# 1 <= intervals.length <= 105
# 	intervals[i].length == 2
# 	1 <= lefti <= righti <= 106
#

class Solution(object):
    def minGroups(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: int
        """
        events = []
        for start, end in intervals:
            events.append((start, 1))   # interval starts
            events.append((end + 1, -1)) # interval ends

        events.sort()
        
        current_groups = 0
        max_groups = 0
        
        for _, event_type in events:
            current_groups += event_type
            max_groups = max(max_groups, current_groups)
        
        return max_groups