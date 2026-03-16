# Source: https://leetcode.com/problems/count-complete-subarrays-in-an-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums consisting of positive integers.
#
# We call a subarray of an array complete if the following condition is satisfied:
#
#
# 	The number of distinct elements in the subarray is equal to the number of distinct elements in the whole array.
#
#
# Return the number of complete subarrays.
#
# A subarray is a contiguous non-empty part of an array.
#
# Example:
# Input: nums = [1,3,1,2,2]
# Output: 4
# Explanation: The complete subarrays are the following: [1,3,1,2], [1,3,1,2,2], [3,1,2] and [3,1,2,2].
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i] <= 2000
#

class Solution(object):
    def countCompleteSubarrays(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        total_distinct = len(set(nums))
        n = len(nums)
        count = 0

        for start in range(n):
            seen = set()
            for end in range(start, n):
                seen.add(nums[end])
                if len(seen) == total_distinct:
                    count += 1

        return count