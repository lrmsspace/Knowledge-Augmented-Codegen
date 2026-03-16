# Source: https://leetcode.com/problems/minimum-absolute-difference-between-elements-with-constraint/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums and an integer x.
#
# Find the minimum absolute difference between two elements in the array that are at least x indices apart.
#
# In other words, find two indices i and j such that abs(i - j) >= x and abs(nums[i] - nums[j]) is minimized.
#
# Return an integer denoting the minimum absolute difference between two elements that are at least x indices apart.
#
# Example:
# Input: nums = [4,3,2,4], x = 2
# Output: 0
# Explanation: We can select nums[0] = 4 and nums[3] = 4. 
# They are at least 2 indices apart, and their absolute difference is the minimum, 0. 
# It can be shown that 0 is the optimal answer.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	0 <= x < nums.length
#

class Solution(object):
    def minAbsoluteDifference(self, nums, x):
        """
        :type nums: List[int]
        :type x: int
        :rtype: int
        """
        import bisect
        sorted_list = []
        min_diff = float('inf')
        
        for i in range(x, len(nums)):
            bisect.insort(sorted_list, nums[i - x])
            pos = bisect.bisect_left(sorted_list, nums[i])
            
            if pos < len(sorted_list):
                min_diff = min(min_diff, abs(sorted_list[pos] - nums[i]))
            if pos > 0:
                min_diff = min(min_diff, abs(sorted_list[pos - 1] - nums[i]))
        
        return min_diff