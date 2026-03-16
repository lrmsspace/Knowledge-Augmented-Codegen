# Source: https://leetcode.com/problems/beautiful-array/   |   Difficulty: Medium
#
# Problem Description:
# An array nums of length n is beautiful if:
#
#
# 	nums is a permutation of the integers in the range [1, n].
# 	For every 0 <= i < j < n, there is no index k with i < k < j where 2 * nums[k] == nums[i] + nums[j].
#
#
# Given the integer n, return any beautiful array nums of length n. There will be at least one valid answer for the given n.
#
# Example:
# Input: n = 4
# Output: [2,1,4,3]
#
# Constraints:
# 1 <= n <= 1000
#

class Solution(object):
    def beautifulArray(self, n):
        """
        :type n: int
        :rtype: List[int]
        """
        res = [1]
        while len(res) < n:
            res = [x * 2 for x in res if x * 2 <= n] + [x * 2 - 1 for x in res if x * 2 - 1 <= n]
        return res