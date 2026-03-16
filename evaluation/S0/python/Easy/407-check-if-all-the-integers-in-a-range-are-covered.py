# Source: https://leetcode.com/problems/check-if-all-the-integers-in-a-range-are-covered/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 2D integer array ranges and two integers left and right. Each ranges[i] = [starti, endi] represents an inclusive interval between starti and endi.
#
# Return true if each integer in the inclusive range [left, right] is covered by at least one interval in ranges. Return false otherwise.
#
# An integer x is covered by an interval ranges[i] = [starti, endi] if starti <= x <= endi.
#
# Example:
# Input: ranges = [[1,2],[3,4],[5,6]], left = 2, right = 5
# Output: true
# Explanation: Every integer between 2 and 5 is covered:
# - 2 is covered by the first range.
# - 3 and 4 are covered by the second range.
# - 5 is covered by the third range.
#
# Constraints:
# 1 <= ranges.length <= 50
# 	1 <= starti <= endi <= 50
# 	1 <= left <= right <= 50
#

class Solution(object):
    def isCovered(self, ranges, left, right):
        """
        :type ranges: List[List[int]]
        :type left: int
        :type right: int
        :rtype: bool
        """
        covered = [False] * 51  # Since the maximum number is 50

        for start, end in ranges:
            for i in range(start, end + 1):
                covered[i] = True

        for num in range(left, right + 1):
            if not covered[num]:
                return False

        return True