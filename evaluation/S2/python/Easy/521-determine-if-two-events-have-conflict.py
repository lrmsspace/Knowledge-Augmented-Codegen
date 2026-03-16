# Source: https://leetcode.com/problems/determine-if-two-events-have-conflict/   |   Difficulty: Easy
#
# Problem Description:
# You are given two arrays of strings that represent two inclusive events that happened on the same day, event1 and event2, where:
#
#
# 	event1 = [startTime1, endTime1] and
# 	event2 = [startTime2, endTime2].
#
#
# Event times are valid 24 hours format in the form of HH:MM.
#
# A conflict happens when two events have some non-empty intersection (i.e., some moment is common to both events).
#
# Return true if there is a conflict between two events. Otherwise, return false.
#
# Example:
# Input: event1 = ["01:15","02:00"], event2 = ["02:00","03:00"]
# Output: true
# Explanation: The two events intersect at time 2:00.
#
# Constraints:
# event1.length == event2.length == 2
# 	event1[i].length == event2[i].length == 5
# 	startTime1 <= endTime1
# 	startTime2 <= endTime2
# 	All the event times follow the HH:MM format.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def haveConflict(self, event1, event2):
        """
        :type event1: List[str]
        :type event2: List[str]
        :rtype: bool
        """
        # Convert time from "HH:MM" to total minutes
        def time_to_minutes(t):
            h, m = map(int, t.split(':'))
            return h * 60 + m
        
        start1, end1 = time_to_minutes(event1[0]), time_to_minutes(event1[1])
        start2, end2 = time_to_minutes(event2[0]), time_to_minutes(event2[1])
        
        # Check for conflict
        return not (end1 <= start2 or end2 <= start1)