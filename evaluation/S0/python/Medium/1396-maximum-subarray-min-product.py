# Source: https://leetcode.com/problems/maximum-subarray-min-product/   |   Difficulty: Medium
#
# Problem Description:
# The min-product of an array is equal to the minimum value in the array multiplied by the array's sum.
#
#
# 	For example, the array [3,2,5] (minimum value is 2) has a min-product of 2 * (3+2+5) = 2 * 10 = 20.
#
#
# Given an array of integers nums, return the maximum min-product of any non-empty subarray of nums. Since the answer may be large, return it modulo 109 + 7.
#
# Note that the min-product should be maximized before performing the modulo operation. Testcases are generated such that the maximum min-product without modulo will fit in a 64-bit signed integer.
#
# A subarray is a contiguous part of an array.
#
# Example:
# Input: nums = [1,2,3,2]
# Output: 14
# Explanation: The maximum min-product is achieved with the subarray [2,3,2] (minimum value is 2).
# 2 * (2+3+2) = 2 * 7 = 14.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 107
#

class Solution(object):
    def maxSumMinProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        
        # 前缀和
        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + nums[i]
        
        # 单调栈寻找每个元素的左边界和右边界
        left, right = [-1] * n, [n] * n
        stack = []
        
        for i in range(n):
            while stack and nums[stack[-1]] >= nums[i]:
                stack.pop()
            left[i] = stack[-1] if stack else -1
            stack.append(i)
        
        stack.clear()
        
        for i in range(n - 1, -1, -1):
            while stack and nums[stack[-1]] >= nums[i]:
                stack.pop()
            right[i] = stack[-1] if stack else n
            stack.append(i)
        
        # 计算最大最小乘积
        max_product = 0
        for i in range(n):
            total_sum = prefix_sum[right[i]] - prefix_sum[left[i] + 1]
            max_product = max(max_product, nums[i] * total_sum)
        
        return max_product % MOD