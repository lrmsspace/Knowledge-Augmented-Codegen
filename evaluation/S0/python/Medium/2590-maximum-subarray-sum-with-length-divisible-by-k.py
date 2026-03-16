# Source: https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of integers nums and an integer k.
#
# Return the maximum sum of a subarray of nums, such that the size of the subarray is divisible by k.
#
# Example:
# Input: nums = [1,2], k = 1
#
# Output: 3
#
# Explanation:
#
# The subarray [1, 2] with sum 3 has length equal to 2 which is divisible by 1.
#
# Constraints:
# 1 <= k <= nums.length <= 2 * 105
# 	-109 <= nums[i] <= 109
#

class Solution(object):
    def maxSubarraySum(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + nums[i]

        mod_map = {}
        max_sum = float('-inf')

        for i in range(n + 1):
            mod = i % k
            if mod in mod_map:
                prev_index = mod_map[mod]
                current_sum = prefix_sum[i] - prefix_sum[prev_index]
                max_sum = max(max_sum, current_sum)
            else:
                mod_map[mod] = i

        return max_sum if max_sum != float('-inf') else 0