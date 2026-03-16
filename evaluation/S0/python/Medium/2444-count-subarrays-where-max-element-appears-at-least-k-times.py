# Source: https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and a positive integer k.
#
# Return the number of subarrays where the maximum element of nums appears at least k times in that subarray.
#
# A subarray is a contiguous sequence of elements within an array.
#
# Example:
# Input: nums = [1,3,2,3,3], k = 2
# Output: 6
# Explanation: The subarrays that contain the element 3 at least 2 times are: [1,3,2,3], [1,3,2,3,3], [3,2,3], [3,2,3,3], [2,3,3] and [3,3].
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 106
# 	1 <= k <= 105
#

class Solution(object):
    def countSubarrays(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        total_subarrays = n * (n + 1) // 2
        
        def count_subarrays_with_max_less_than_k():
            count = 0
            length = 0
            
            for num in nums:
                if num < k:
                    length += 1
                else:
                    count += length * (length + 1) // 2
                    length = 0
            
            count += length * (length + 1) // 2
            return count
        
        subarrays_with_max_less_than_k = count_subarrays_with_max_less_than_k()
        return total_subarrays - subarrays_with_max_less_than_k