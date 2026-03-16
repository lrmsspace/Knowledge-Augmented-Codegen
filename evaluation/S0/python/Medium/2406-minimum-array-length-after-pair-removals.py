# Source: https://leetcode.com/problems/minimum-array-length-after-pair-removals/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array num sorted in non-decreasing order.
#
# You can perform the following operation any number of times:
#
#
# 	Choose two indices, i and j, where nums[i] < nums[j].
# 	Then, remove the elements at indices i and j from nums. The remaining elements retain their original order, and the array is re-indexed.
#
#
# Return the minimum length of nums after applying the operation zero or more times.
#
# Example:
# Input: nums = [1,2,3,4]
#
# Output: 0
#
# Explanation:
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	nums is sorted in non-decreasing order.
#

class Solution(object):
    def minLengthAfterRemovals(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        left, right = 0, len(nums) - 1
        removed_pairs = 0

        while left < right:
            if nums[left] < nums[right]:
                removed_pairs += 1
                left += 1
                right -= 1
            else:
                right -= 1

        return len(nums) - 2 * removed_pairs