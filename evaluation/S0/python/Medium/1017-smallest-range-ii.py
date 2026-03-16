# Source: https://leetcode.com/problems/smallest-range-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and an integer k.
#
# For each index i where 0 <= i < nums.length, change nums[i] to be either nums[i] + k or nums[i] - k.
#
# The score of nums is the difference between the maximum and minimum elements in nums.
#
# Return the minimum score of nums after changing the values at each index.
#
# Example:
# Input: nums = [1], k = 0
# Output: 0
# Explanation: The score is max(nums) - min(nums) = 1 - 1 = 0.
#
# Constraints:
# 1 <= nums.length <= 104
# 	0 <= nums[i] <= 104
# 	0 <= k <= 104
#

class Solution(object):
    def smallestRangeII(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        nums.sort()
        res = nums[-1] - nums[0]
        for i in range(len(nums) - 1):
            high = max(nums[i] + k, nums[-1] - k)
            low = min(nums[i + 1] - k, nums[0] + k)
            res = min(res, high - low)
        return res