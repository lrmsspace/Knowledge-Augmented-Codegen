# Source: https://leetcode.com/problems/find-the-median-of-the-uniqueness-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums. The uniqueness array of nums is the sorted array that contains the number of distinct elements of all the subarrays of nums. In other words, it is a sorted array consisting of distinct(nums[i..j]), for all 0 <= i <= j < nums.length.
#
# Here, distinct(nums[i..j]) denotes the number of distinct elements in the subarray that starts at index i and ends at index j.
#
# Return the median of the uniqueness array of nums.
#
# Note that the median of an array is defined as the middle element of the array when it is sorted in non-decreasing order. If there are two choices for a median, the smaller of the two values is taken.
#
# Example:
# Input: nums = [1,2,3]
#
# Output: 1
#
# Explanation:
#
# The uniqueness array of nums is [distinct(nums[0..0]), distinct(nums[1..1]), distinct(nums[2..2]), distinct(nums[0..1]), distinct(nums[1..2]), distinct(nums[0..2])] which is equal to [1, 1, 1, 2, 2, 3]. The uniqueness array has a median of 1. Therefore, the answer is 1.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 105
#

class Solution(object):
    def medianOfUniquenessArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        total_subarrays = n * (n + 1) // 2
        median_pos = (total_subarrays + 1) // 2

        left, right = 1, n
        result = -1

        while left <= right:
            mid = (left + right) // 2
            count = self.count_subarrays_with_at_most_k_distinct(nums, mid)

            if count >= median_pos:
                result = mid
                right = mid - 1
            else:
                left = mid + 1

        return result