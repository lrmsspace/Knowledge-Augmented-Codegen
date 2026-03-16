# Source: https://leetcode.com/problems/minimum-sum-of-mountain-triplets-i/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed array nums of integers.
#
# A triplet of indices (i, j, k) is a mountain if:
#
#
# 	i < j < k
# 	nums[i] < nums[j] and nums[k] < nums[j]
#
#
# Return the minimum possible sum of a mountain triplet of nums. If no such triplet exists, return -1.
#
# Example:
# Input: nums = [8,6,1,5,3]
# Output: 9
# Explanation: Triplet (2, 3, 4) is a mountain triplet of sum 9 since: 
# - 2 < 3 < 4
# - nums[2] < nums[3] and nums[4] < nums[3]
# And the sum of this triplet is nums[2] + nums[3] + nums[4] = 9. It can be shown that there are no mountain triplets with a sum of less than 9.
#
# Constraints:
# 3 <= nums.length <= 50
# 	1 <= nums[i] <= 50
#

class Solution(object):
    def minimumSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        min_sum = float('inf')
        
        for j in range(1, n-1):
            left_min = float('inf')
            right_min = float('inf')
            
            # Find the minimum on the left side
            for i in range(j):
                if nums[i] < nums[j]:
                    left_min = min(left_min, nums[i])
            
            # Find the minimum on the right side
            for k in range(j+1, n):
                if nums[k] < nums[j]:
                    right_min = min(right_min, nums[k])
            
            if left_min != float('inf') and right_min != float('inf'):
                current_sum = left_min + nums[j] + right_min
                min_sum = min(min_sum, current_sum)
        
        return min_sum if min_sum != float('inf') else -1