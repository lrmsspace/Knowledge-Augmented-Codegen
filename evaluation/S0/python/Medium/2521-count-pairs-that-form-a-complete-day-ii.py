# Source: https://leetcode.com/problems/count-pairs-that-form-a-complete-day-ii/   |   Difficulty: Medium
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
# Explanation: The pairs of indices that form a complete day are (0, 1) and (3, 4).
#
# Constraints:
# 1 <= hours.length <= 5 * 105
# 	1 <= hours[i] <= 109
#

class Solution(object):
    def countCompleteDayPairs(self, hours):
        """
        :type hours: List[int]
        :rtype: int
        """
        mod_count = {}
        count = 0
        
        for hour in hours:
            mod = hour % 24
            complement = (24 - mod) % 24
            
            if complement in mod_count:
                count += mod_count[complement]
            
            if mod in mod_count:
                mod_count[mod] += 1
            else:
                mod_count[mod] = 1
        
        return count