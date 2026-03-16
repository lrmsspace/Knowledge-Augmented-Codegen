# Source: https://leetcode.com/problems/range-sum-of-sorted-subarray-sums/   |   Difficulty: Medium
#
# Problem Description:
# You are given the array nums consisting of n positive integers. You computed the sum of all non-empty continuous subarrays from the array and then sorted them in non-decreasing order, creating a new array of n * (n + 1) / 2 numbers.
#
# Return the sum of the numbers from index left to index right (indexed from 1), inclusive, in the new array. Since the answer can be a huge number return it modulo 109 + 7.
#
# Example:
# Input: nums = [1,2,3,4], n = 4, left = 1, right = 5
# Output: 13 
# Explanation: All subarray sums are 1, 3, 6, 10, 2, 5, 9, 3, 7, 4. After sorting them in non-decreasing order we have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10]. The sum of the numbers from index le = 1 to ri = 5 is 1 + 2 + 3 + 3 + 4 = 13.
#
# Constraints:
# n == nums.length
# 	1 <= nums.length <= 1000
# 	1 <= nums[i] <= 100
# 	1 <= left <= right <= n * (n + 1) / 2
#

class Solution(object):
    def rangeSum(self, nums, n, left, right):
        """
        :type nums: List[int]
        :type n: int
        :type left: int
        :type right: int
        :rtype: int
        """
        MOD = 10**9 + 7
        subarray_sums = []
        
        # Generate all possible subarray sums
        for i in range(n):
            current_sum = 0
            for j in range(i, n):
                current_sum += nums[j]
                subarray_sums.append(current_sum)
        
        # Sort the subarray sums
        subarray_sums.sort()
        
        # Calculate the sum from index left to right (1-based indexing)
        result = sum(subarray_sums[left-1:right]) % MOD
        
        return result