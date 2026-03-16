# Source: https://leetcode.com/problems/count-the-number-of-good-subarrays/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums and an integer k, return the number of good subarrays of nums.
#
# A subarray arr is good if there are at least k pairs of indices (i, j) such that i < j and arr[i] == arr[j].
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [1,1,1,1,1], k = 10
# Output: 1
# Explanation: The only good subarray is the array nums itself.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i], k <= 109
#

class Solution(object):
    def countGood(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from collections import defaultdict

        count = defaultdict(int)
        left = 0
        total_pairs = 0
        result = 0

        for right in range(len(nums)):
            total_pairs += count[nums[right]]
            count[nums[right]] += 1

            while total_pairs >= k:
                result += len(nums) - right
                count[nums[left]] -= 1
                total_pairs -= count[nums[left]]
                left += 1

        return result