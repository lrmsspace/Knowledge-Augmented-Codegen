# Source: https://leetcode.com/problems/subarray-sum-equals-k/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [1,1,1], k = 2
# Output: 2
#
# Constraints:
# 1 <= nums.length <= 2 * 104
# 	-1000 <= nums[i] <= 1000
# 	-107 <= k <= 107
#

class Solution(object):
    def subarraySum(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        count = 0
        sum_map = {0: 1}
        current_sum = 0
        
        for num in nums:
            current_sum += num
            if (current_sum - k) in sum_map:
                count += sum_map[current_sum - k]
            sum_map[current_sum] = sum_map.get(current_sum, 0) + 1
        
        return count