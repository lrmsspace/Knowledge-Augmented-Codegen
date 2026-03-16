# Source: https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and an integer k. Find the maximum subarray sum of all the subarrays of nums that meet the following conditions:
#
#
# 	The length of the subarray is k, and
# 	All the elements of the subarray are distinct.
#
#
# Return the maximum subarray sum of all the subarrays that meet the conditions. If no subarray meets the conditions, return 0.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [1,5,4,2,9,9,9], k = 3
# Output: 15
# Explanation: The subarrays of nums with length 3 are:
# - [1,5,4] which meets the requirements and has a sum of 10.
# - [5,4,2] which meets the requirements and has a sum of 11.
# - [4,2,9] which meets the requirements and has a sum of 15.
# - [2,9,9] which does not meet the requirements because the element 9 is repeated.
# - [9,9,9] which does not meet the requirements because the element 9 is repeated.
# We return 15 because it is the maximum subarray sum of all the subarrays that meet the conditions
#
# Constraints:
# 1 <= k <= nums.length <= 105
# 	1 <= nums[i] <= 105
#

class Solution(object):
    def maximumSubarraySum(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        if k > n:
            return 0

        num_count = {}
        current_sum = 0
        max_sum = 0

        for i in range(n):
            # Add the current number to the window
            num_count[nums[i]] = num_count.get(nums[i], 0) + 1
            current_sum += nums[i]

            # Remove the number that is left out of the window
            if i >= k:
                left_num = nums[i - k]
                num_count[left_num] -= 1
                current_sum -= left_num
                if num_count[left_num] == 0:
                    del num_count[left_num]

            # Check if all elements in the current window are distinct
            if i >= k - 1:
                if len(num_count) == k:
                    max_sum = max(max_sum, current_sum)

        return max_sum