# Source: https://leetcode.com/problems/subarrays-with-k-different-integers/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer array nums and an integer k, return the number of good subarrays of nums.
#
# A good array is an array where the number of different integers in that array is exactly k.
#
#
# 	For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.
#
#
# A subarray is a contiguous part of an array.
#
# Example:
# Input: nums = [1,2,1,2,3], k = 2
# Output: 7
# Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]
#
# Constraints:
# 1 <= nums.length <= 2 * 104
# 	1 <= nums[i], k <= nums.length
#

class Solution(object):
    def subarraysWithKDistinct(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        def at_most_k_distinct(nums, k):
            count = {}
            left = 0
            result = 0

            for right in range(len(nums)):
                count[nums[right]] = count.get(nums[right], 0) + 1

                while len(count) > k:
                    count[nums[left]] -= 1
                    if count[nums[left]] == 0:
                        del count[nums[left]]
                    left += 1

                result += right - left + 1

            return result

        return at_most_k_distinct(nums, k) - at_most_k_distinct(nums, k - 1)