# Source: https://leetcode.com/problems/maximum-or/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums of length n and an integer k. In an operation, you can choose an element and multiply it by 2.
#
# Return the maximum possible value of nums[0] | nums[1] | ... | nums[n - 1] that can be obtained after applying the operation on nums at most k times.
#
# Note that a | b denotes the bitwise or between two integers a and b.
#
# Example:
# Input: nums = [12,9], k = 1
# Output: 30
# Explanation: If we apply the operation to index 1, our new array nums will be equal to [12,18]. Thus, we return the bitwise or of 12 and 18, which is 30.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	1 <= k <= 15
#

class Solution(object):
    def maximumOr(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        prefix_or = [0] * (n + 1)
        suffix_or = [0] * (n + 1)

        for i in range(n):
            prefix_or[i + 1] = prefix_or[i] | nums[i]

        for i in range(n - 1, -1, -1):
            suffix_or[i] = suffix_or[i + 1] | nums[i]

        max_value = 0
        for i in range(n):
            modified_value = nums[i] << k
            current_or = prefix_or[i] | modified_value | suffix_or[i + 1]
            max_value = max(max_value, current_or)

        return max_value