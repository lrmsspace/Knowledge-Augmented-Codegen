# Source: https://leetcode.com/problems/split-array-largest-sum/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.
#
# Return the minimized largest sum of the split.
#
# A subarray is a contiguous part of the array.
#
# Example:
# Input: nums = [7,2,5,10,8], k = 2
# Output: 18
# Explanation: There are four ways to split nums into two subarrays.
# The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	0 <= nums[i] <= 106
# 	1 <= k <= min(50, nums.length)
#

class Solution(object):
    def splitArray(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        def can_split(max_sum):
            current_sum = 0
            splits = 1
            for num in nums:
                current_sum += num
                if current_sum > max_sum:
                    splits += 1
                    current_sum = num
                    if splits > k:
                        return False
            return True

        left, right = max(nums), sum(nums)
        while left < right:
            mid = (left + right) // 2
            if can_split(mid):
                right = mid
            else:
                left = mid + 1
        return left