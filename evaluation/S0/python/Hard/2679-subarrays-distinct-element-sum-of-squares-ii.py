# Source: https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array nums.
#
# The distinct count of a subarray of nums is defined as:
#
#
# 	Let nums[i..j] be a subarray of nums consisting of all the indices from i to j such that 0 <= i <= j < nums.length. Then the number of distinct values in nums[i..j] is called the distinct count of nums[i..j].
#
#
# Return the sum of the squares of distinct counts of all subarrays of nums.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [1,2,1]
# Output: 15
# Explanation: Six possible subarrays are:
# [1]: 1 distinct value
# [2]: 1 distinct value
# [1]: 1 distinct value
# [1,2]: 2 distinct values
# [2,1]: 2 distinct values
# [1,2,1]: 2 distinct values
# The sum of the squares of the distinct counts in all subarrays is equal to 12 + 12 + 12 + 22 + 22 + 22 = 15.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 105
#

class Solution(object):
    def sumCounts(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        last_occurrence = {}
        total_sum = 0
        current_distinct_count = 0
        left = 0

        for right in range(n):
            if nums[right] not in last_occurrence or last_occurrence[nums[right]] < left:
                current_distinct_count += 1
            else:
                left = last_occurrence[nums[right]] + 1

            last_occurrence[nums[right]] = right
            total_sum = (total_sum + current_distinct_count * current_distinct_count) % MOD

        return total_sum