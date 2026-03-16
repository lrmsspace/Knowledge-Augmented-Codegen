# Source: https://leetcode.com/problems/maximum-consecutive-floors-without-special-floors/   |   Difficulty: Medium
#
# Problem Description:
# Alice manages a company and has rented some floors of a building as office space. Alice has decided some of these floors should be special floors, used for relaxation only.
#
# You are given two integers bottom and top, which denote that Alice has rented all the floors from bottom to top (inclusive). You are also given the integer array special, where special[i] denotes a special floor that Alice has designated for relaxation.
#
# Return the maximum number of consecutive floors without a special floor.
#
# Example:
# Input: bottom = 2, top = 9, special = [4,6]
# Output: 3
# Explanation: The following are the ranges (inclusive) of consecutive floors without a special floor:
# - (2, 3) with a total amount of 2 floors.
# - (5, 5) with a total amount of 1 floor.
# - (7, 9) with a total amount of 3 floors.
# Therefore, we return the maximum number which is 3 floors.
#
# Constraints:
# 1 <= special.length <= 105
# 	1 <= bottom <= special[i] <= top <= 109
# 	All the values of special are unique.
#

class Solution(object):
    def maxConsecutive(self, bottom, top, special):
        """
        :type bottom: int
        :type top: int
        :type special: List[int]
        :rtype: int
        """
        special.sort()
        max_gap = max(special[0] - bottom, top - special[-1])
        
        for i in range(1, len(special)):
            gap = special[i] - special[i - 1] - 1
            max_gap = max(max_gap, gap)
        
        return max_gap