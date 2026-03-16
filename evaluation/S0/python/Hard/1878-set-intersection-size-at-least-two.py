# Source: https://leetcode.com/problems/set-intersection-size-at-least-two/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D integer array intervals where intervals[i] = [starti, endi] represents all the integers from starti to endi inclusively.
#
# A containing set is an array nums where each interval from intervals has at least two integers in nums.
#
#
# 	For example, if intervals = [[1,3], [3,7], [8,9]], then [1,2,4,7,8,9] and [2,3,4,8,9] are containing sets.
#
#
# Return the minimum possible size of a containing set.
#
# Example:
# Input: intervals = [[1,3],[3,7],[8,9]]
# Output: 5
# Explanation: let nums = [2, 3, 4, 8, 9].
# It can be shown that there cannot be any containing array of size 4.
#
# Constraints:
# 1 <= intervals.length <= 3000
# 	intervals[i].length == 2
# 	0 <= starti < endi <= 108
#

class Solution(object):
    def intersectionSizeTwo(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: int
        """
        intervals.sort(key=lambda x: (x[1], -x[0]))
        res = []
        
        for interval in intervals:
            start, end = interval
            count = 0
            
            for num in res[-2:]:
                if start <= num <= end:
                    count += 1
            
            if count == 0:
                res.append(end - 1)
                res.append(end)
            elif count == 1:
                if res[-1] == end:
                    res.append(end - 1)
                else:
                    res.append(end)
        
        return len(res)