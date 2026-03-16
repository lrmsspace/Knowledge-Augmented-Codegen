# Source: https://leetcode.com/problems/sort-even-and-odd-indices-independently/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed integer array nums. Rearrange the values of nums according to the following rules:
#
#
# 	Sort the values at odd indices of nums in non-increasing order.
#
# 	
# 		For example, if nums = [4,1,2,3] before this step, it becomes [4,3,2,1] after. The values at odd indices 1 and 3 are sorted in non-increasing order.
# 	
# 	
# 	Sort the values at even indices of nums in non-decreasing order.
# 	
# 		For example, if nums = [4,1,2,3] before this step, it becomes [2,1,4,3] after. The values at even indices 0 and 2 are sorted in non-decreasing order.
# 	
# 	
#
#
# Return the array formed after rearranging the values of nums.
#
# Example:
# Input: nums = [4,1,2,3]
# Output: [2,3,4,1]
# Explanation: 
# First, we sort the values present at odd indices (1 and 3) in non-increasing order.
# So, nums changes from [4,1,2,3] to [4,3,2,1].
# Next, we sort the values present at even indices (0 and 2) in non-decreasing order.
# So, nums changes from [4,1,2,3] to [2,3,4,1].
# Thus, the array formed after rearranging the values is [2,3,4,1].
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 100
#

class Solution(object):
    def sortEvenOdd(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        even_indices = sorted([nums[i] for i in range(0, len(nums), 2)])
        odd_indices = sorted([nums[i] for i in range(1, len(nums), 2)], reverse=True)
        
        result = []
        even_ptr, odd_ptr = 0, 0
        
        for i in range(len(nums)):
            if i % 2 == 0:
                result.append(even_indices[even_ptr])
                even_ptr += 1
            else:
                result.append(odd_indices[odd_ptr])
                odd_ptr += 1
                
        return result