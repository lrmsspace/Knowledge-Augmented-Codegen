# Source: https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-i/   |   Difficulty: Easy
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
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 100
#

class Solution(object):
    def sumCounts(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        total_sum = 0
        
        for i in range(n):
            distinct_elements = set()
            for j in range(i, n):
                distinct_elements.add(nums[j])
                distinct_count = len(distinct_elements)
                total_sum += distinct_count * distinct_count
                
        return total_sum