# Source: https://leetcode.com/problems/maximum-erasure-value/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of positive integers nums and want to erase a subarray containing unique elements. The score you get by erasing the subarray is equal to the sum of its elements.
#
# Return the maximum score you can get by erasing exactly one subarray.
#
# An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, if it is equal to a[l],a[l+1],...,a[r] for some (l,r).
#
# Example:
# Input: nums = [4,2,4,5,6]
# Output: 17
# Explanation: The optimal subarray here is [2,4,5,6].
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 104
#

class Solution(object):
    def maximumUniqueSubarray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        num_set = set()
        left = 0
        current_sum = 0
        max_sum = 0
        
        for right in range(len(nums)):
            while nums[right] in num_set:
                num_set.remove(nums[left])
                current_sum -= nums[left]
                left += 1
            
            num_set.add(nums[right])
            current_sum += nums[right]
            max_sum = max(max_sum, current_sum)
        
        return max_sum