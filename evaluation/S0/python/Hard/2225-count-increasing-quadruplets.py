# Source: https://leetcode.com/problems/count-increasing-quadruplets/   |   Difficulty: Hard
#
# Problem Description:
# Given a 0-indexed integer array nums of size n containing all numbers from 1 to n, return the number of increasing quadruplets.
#
# A quadruplet (i, j, k, l) is increasing if:
#
#
# 	0 <= i < j < k < l < n, and
# 	nums[i] < nums[k] < nums[j] < nums[l].
#
# Example:
# Input: nums = [1,3,2,4,5]
# Output: 2
# Explanation: 
# - When i = 0, j = 1, k = 2, and l = 3, nums[i] < nums[k] < nums[j] < nums[l].
# - When i = 0, j = 1, k = 2, and l = 4, nums[i] < nums[k] < nums[j] < nums[l]. 
# There are no other quadruplets, so we return 2.
#
# Constraints:
# 4 <= nums.length <= 4000
# 	1 <= nums[i] <= nums.length
# 	All the integers of nums are unique. nums is a permutation.
#

class Solution(object):
    def countQuadruplets(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        count = 0
        
        for j in range(1, n - 2):
            for k in range(j + 1, n - 1):
                if nums[k] < nums[j]:
                    left_count = sum(1 for i in range(j) if nums[i] < nums[k])
                    right_count = sum(1 for l in range(k + 1, n) if nums[l] > nums[j])
                    count += left_count * right_count
                    
        return count