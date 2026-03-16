# Source: https://leetcode.com/problems/check-if-it-is-possible-to-split-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums of length n and an integer m. You need to determine if it is possible to split the array into n arrays of size 1 by performing a series of steps.
#
# An array is called good if:
#
#
# 	The length of the array is one, or
# 	The sum of the elements of the array is greater than or equal to m.
#
#
# In each step, you can select an existing array (which may be the result of previous steps) with a length of at least two and split it into two arrays, if both resulting arrays are good.
#
# Return true if you can split the given array into n arrays, otherwise return false.
#
# Example:
# Input: nums = [2, 2, 1], m = 4
#
# Output: true
#
# Explanation:
#
#
# 	Split [2, 2, 1] to [2, 2] and [1]. The array [1] has a length of one, and the array [2, 2] has the sum of its elements equal to 4 >= m, so both are good arrays.
# 	Split [2, 2] to [2] and [2]. both arrays have the length of one, so both are good arrays.
#
# Constraints:
# 1 <= n == nums.length <= 100
# 	1 <= nums[i] <= 100
# 	1 <= m <= 200
#

class Solution(object):
    def canSplitArray(self, nums, m):
        """
        :type nums: List[int]
        :type m: int
        :rtype: bool
        """
        n = len(nums)
        if n <= 2:
            return True
        
        for i in range(1, n - 1):
            if nums[i - 1] + nums[i] < m and nums[i] + nums[i + 1] < m:
                return False
        
        return True