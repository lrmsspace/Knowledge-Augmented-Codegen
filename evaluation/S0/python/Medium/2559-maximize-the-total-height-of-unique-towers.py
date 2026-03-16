# Source: https://leetcode.com/problems/maximize-the-total-height-of-unique-towers/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array maximumHeight, where maximumHeight[i] denotes the maximum height the ith tower can be assigned.
#
# Your task is to assign a height to each tower so that:
#
#
# 	The height of the ith tower is a positive integer and does not exceed maximumHeight[i].
# 	No two towers have the same height.
#
#
# Return the maximum possible total sum of the tower heights. If it's not possible to assign heights, return -1.
#
# Example:
# Input: maximumHeight = [2,3,4,3]
#
# Output: 10
#
# Explanation:
#
# We can assign heights in the following way: [1, 2, 4, 3].
#
# Constraints:
# 1 <= maximumHeight.length <= 105
# 	1 <= maximumHeight[i] <= 109
#

class Solution(object):
    def maximumTotalSum(self, maximumHeight):
        """
        :type maximumHeight: List[int]
        :rtype: int
        """
        maximumHeight.sort(reverse=True)
        used_heights = set()
        total_sum = 0

        for height in maximumHeight:
            while height > 0 and height in used_heights:
                height -= 1
            if height == 0:
                return -1
            used_heights.add(height)
            total_sum += height

        return total_sum