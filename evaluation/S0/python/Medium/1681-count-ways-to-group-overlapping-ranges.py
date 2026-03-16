# Source: https://leetcode.com/problems/count-ways-to-group-overlapping-ranges/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D integer array ranges where ranges[i] = [starti, endi] denotes that all integers between starti and endi (both inclusive) are contained in the ith range.
#
# You are to split ranges into two (possibly empty) groups such that:
#
#
# 	Each range belongs to exactly one group.
# 	Any two overlapping ranges must belong to the same group.
#
#
# Two ranges are said to be overlapping if there exists at least one integer that is present in both ranges.
#
#
# 	For example, [1, 3] and [2, 5] are overlapping because 2 and 3 occur in both ranges.
#
#
# Return the total number of ways to split ranges into two groups. Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: ranges = [[6,10],[5,15]]
# Output: 2
# Explanation: 
# The two ranges are overlapping, so they must be in the same group.
# Thus, there are two possible ways:
# - Put both the ranges together in group 1.
# - Put both the ranges together in group 2.
#
# Constraints:
# 1 <= ranges.length <= 105
# 	ranges[i].length == 2
# 	0 <= starti <= endi <= 109
#

class Solution(object):
    def countWays(self, ranges):
        """
        :type ranges: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        ranges.sort()
        
        merged_ranges = []
        current_start, current_end = ranges[0]
        
        for start, end in ranges[1:]:
            if start <= current_end:
                current_end = max(current_end, end)
            else:
                merged_ranges.append((current_start, current_end))
                current_start, current_end = start, end
        
        merged_ranges.append((current_start, current_end))
        
        # The number of ways to split the ranges is 2^(number of merged ranges)
        return pow(2, len(merged_ranges), MOD)