# Source: https://leetcode.com/problems/maximum-good-subarray-sum/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums of length n and a positive integer k.
#
# A subarray of nums is called good if the absolute difference between its first and last element is exactly k, in other words, the subarray nums[i..j] is good if |nums[i] - nums[j]| == k.
#
# Return the maximum sum of a good subarray of nums. If there are no good subarrays, return 0.
#
# Example:
# Input: nums = [1,2,3,4,5,6], k = 1
# Output: 11
# Explanation: The absolute difference between the first and last element must be 1 for a good subarray. All the good subarrays are: [1,2], [2,3], [3,4], [4,5], and [5,6]. The maximum subarray sum is 11 for the subarray [5,6].
#
# Constraints:
# 2 <= nums.length <= 105
# 	-109 <= nums[i] <= 109
# 	1 <= k <= 109
#

class Solution(object):
    def maximumSubarraySum(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + nums[i]

        max_sum = 0
        for i in range(n):
            for j in range(i + 1, n):
                if abs(nums[i] - nums[j]) == k:
                    current_sum = prefix_sum[j + 1] - prefix_sum[i]
                    max_sum = max(max_sum, current_sum)

        return max_sum