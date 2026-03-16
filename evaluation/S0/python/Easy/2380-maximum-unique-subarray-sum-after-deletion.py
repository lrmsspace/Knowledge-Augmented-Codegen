# Source: https://leetcode.com/problems/maximum-unique-subarray-sum-after-deletion/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums.
#
# You are allowed to delete any number of elements from nums without making it empty. After performing the deletions, select a subarray of nums such that:
#
#
# 	All elements in the subarray are unique.
# 	The sum of the elements in the subarray is maximized.
#
#
# Return the maximum sum of such a subarray.
#
# Example:
# Input: nums = [1,2,3,4,5]
#
# Output: 15
#
# Explanation:
#
# Select the entire array without deleting any element to obtain the maximum sum.
#
# Constraints:
# 1 <= nums.length <= 100
# 	-100 <= nums[i] <= 100
#

class Solution(object):
    def maxSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        seen = set()
        left = 0
        current_sum = 0
        max_sum = 0
        
        for right in range(len(nums)):
            while nums[right] in seen:
                seen.remove(nums[left])
                current_sum -= nums[left]
                left += 1
            
            seen.add(nums[right])
            current_sum += nums[right]
            max_sum = max(max_sum, current_sum)
        
        return max_sum