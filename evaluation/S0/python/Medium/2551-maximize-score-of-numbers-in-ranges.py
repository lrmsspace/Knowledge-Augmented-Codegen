# Source: https://leetcode.com/problems/maximize-score-of-numbers-in-ranges/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of integers start and an integer d, representing n intervals [start[i], start[i] + d].
#
# You are asked to choose n integers where the ith integer must belong to the ith interval. The score of the chosen integers is defined as the minimum absolute difference between any two integers that have been chosen.
#
# Return the maximum possible score of the chosen integers.
#
# Example:
# Input: start = [6,0,3], d = 2
#
# Output: 4
#
# Explanation:
#
# The maximum possible score can be obtained by choosing integers: 8, 0, and 4. The score of these chosen integers is min(|8 - 0|, |8 - 4|, |0 - 4|) which equals 4.
#
# Constraints:
# 2 <= start.length <= 105
# 	0 <= start[i] <= 109
# 	0 <= d <= 109
#

class Solution(object):
    def maxPossibleScore(self, start, d):
        """
        :type start: List[int]
        :type d: int
        :rtype: int
        """
        start.sort()
        left, right = 0, 10**10
        
        def can_achieve(score):
            prev = start[0]
            for i in range(1, len(start)):
                next_pos = max(prev + score, start[i])
                if next_pos > start[i] + d:
                    return False
                prev = next_pos
            return True
        
        while left < right:
            mid = (left + right + 1) // 2
            if can_achieve(mid):
                left = mid
            else:
                right = mid - 1
        
        return left