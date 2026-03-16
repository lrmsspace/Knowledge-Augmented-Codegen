# Source: https://leetcode.com/problems/largest-time-for-given-digits/   |   Difficulty: Medium
#
# Problem Description:
# Given an array arr of 4 digits, find the latest 24-hour time that can be made using each digit exactly once.
#
# 24-hour times are formatted as "HH:MM", where HH is between 00 and 23, and MM is between 00 and 59. The earliest 24-hour time is 00:00, and the latest is 23:59.
#
# Return the latest 24-hour time in "HH:MM" format. If no valid time can be made, return an empty string.
#
# Example:
# Input: arr = [1,2,3,4]
# Output: "23:41"
# Explanation: The valid 24-hour times are "12:34", "12:43", "13:24", "13:42", "14:23", "14:32", "21:34", "21:43", "23:14", and "23:41". Of these times, "23:41" is the latest.
#
# Constraints:
# arr.length == 4
# 	0 <= arr[i] <= 9
#

class Solution(object):
    def largestTimeFromDigits(self, arr):
        """
        :type arr: List[int]
        :rtype: str
        """
        from itertools import permutations

        max_time = -1
        for perm in permutations(arr):
            h1, h2, m1, m2 = perm
            hours = h1 * 10 + h2
            minutes = m1 * 10 + m2
            if 0 <= hours < 24 and 0 <= minutes < 60:
                total_minutes = hours * 60 + minutes
                max_time = max(max_time, total_minutes)

        if max_time == -1:
            return ""

        max_hours = max_time // 60
        max_minutes = max_time % 60
        return f"{max_hours:02}:{max_minutes:02}"