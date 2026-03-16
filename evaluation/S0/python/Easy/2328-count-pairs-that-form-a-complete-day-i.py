# Source: https://leetcode.com/problems/count-pairs-that-form-a-complete-day-i/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array hours representing times in hours, return an integer denoting the number of pairs i, j where i < j and hours[i] + hours[j] forms a complete day.
#
# A complete day is defined as a time duration that is an exact multiple of 24 hours.
#
# For example, 1 day is 24 hours, 2 days is 48 hours, 3 days is 72 hours, and so on.
#
# Example:
# Input: hours = [12,12,30,24,24]
#
# Output: 2
#
# Explanation:
#
# The pairs of indices that form a complete day are (0, 1) and (3, 4).
#
# Constraints:
# 1 <= hours.length <= 100
# 	1 <= hours[i] <= 109
#

class Solution(object):
    def countCompleteDayPairs(self, hours):
        """
        :type hours: List[int]
        :rtype: int
        """
        count = 0
        n = len(hours)
        
        for i in range(n):
            for j in range(i + 1, n):
                if (hours[i] + hours[j]) % 24 == 0:
                    count += 1
                    
        return count