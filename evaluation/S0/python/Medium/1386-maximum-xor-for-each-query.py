# Source: https://leetcode.com/problems/maximum-xor-for-each-query/   |   Difficulty: Medium
#
# Problem Description:
# You are given a sorted array nums of n non-negative integers and an integer maximumBit. You want to perform the following query n times:
#
#
# 	Find a non-negative integer k < 2maximumBit such that nums[0] XOR nums[1] XOR ... XOR nums[nums.length-1] XOR k is maximized. k is the answer to the ith query.
# 	Remove the last element from the current array nums.
#
#
# Return an array answer, where answer[i] is the answer to the ith query.
#
# Example:
# Input: nums = [0,1,1,3], maximumBit = 2
# Output: [0,3,2,3]
# Explanation: The queries are answered as follows:
# 1st query: nums = [0,1,1,3], k = 0 since 0 XOR 1 XOR 1 XOR 3 XOR 0 = 3.
# 2nd query: nums = [0,1,1], k = 3 since 0 XOR 1 XOR 1 XOR 3 = 3.
# 3rd query: nums = [0,1], k = 2 since 0 XOR 1 XOR 2 = 3.
# 4th query: nums = [0], k = 3 since 0 XOR 3 = 3.
#
# Constraints:
# nums.length == n
# 	1 <= n <= 105
# 	1 <= maximumBit <= 20
# 	0 <= nums[i] < 2maximumBit
# 	nums​​​ is sorted in ascending order.
#

class Solution(object):
    def getMaximumXor(self, nums, maximumBit):
        """
        :type nums: List[int]
        :type maximumBit: int
        :rtype: List[int]
        """
        n = len(nums)
        max_xor = (1 << maximumBit) - 1  # 最大可能的异或值，即2^maximumBit - 1
        current_xor = 0
        
        # 计算初始的全部元素异或值
        for num in nums:
            current_xor ^= num
        
        result = []
        
        # 处理每个查询
        for i in range(n-1, -1, -1):
            # 计算k，使得current_xor XOR k最大化
            k = current_xor ^ max_xor
            result.append(k)
            # 移除最后一个元素的影响
            current_xor ^= nums[i]
        
        return result