# Source: https://leetcode.com/problems/count-alternating-subarrays/   |   Difficulty: Medium
#
# Problem Description:
# You are given a binary array nums.
#
# We call a subarray alternating if no two adjacent elements in the subarray have the same value.
#
# Return the number of alternating subarrays in nums.
#
# Example:
# Input: nums = [0,1,1,1]
#
# Output: 5
#
# Explanation:
#
# The following subarrays are alternating: [0], [1], [1], [1], and [0,1].
#
# Constraints:
# 1 <= nums.length <= 105
# 	nums[i] is either 0 or 1.
#

class Solution(object):
    def countAlternatingSubarrays(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        count = 0
        length = 1  # Length of current alternating subarray

        for i in range(n):
            count += 1  # Single element subarray

            if i > 0:
                if nums[i] != nums[i - 1]:
                    length += 1
                else:
                    length = 1

                count += length - 1  # Add subarrays ending at index i

        return count