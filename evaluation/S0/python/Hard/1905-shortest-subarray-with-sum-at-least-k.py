# Source: https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer array nums and an integer k, return the length of the shortest non-empty subarray of nums with a sum of at least k. If there is no such subarray, return -1.
#
# A subarray is a contiguous part of an array.
#
# Example:
# Input: nums = [1], k = 1
# Output: 1
#
# Constraints:
# 1 <= nums.length <= 105
# 	-105 <= nums[i] <= 105
# 	1 <= k <= 109
#

class Solution(object):
    def shortestSubarray(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from collections import deque
        n = len(nums)
        prefix_sums = [0] * (n + 1)
        
        for i in range(n):
            prefix_sums[i + 1] = prefix_sums[i] + nums[i]
        
        dq = deque()
        min_length = float('inf')
        
        for i in range(n + 1):
            while dq and prefix_sums[i] - prefix_sums[dq[0]] >= k:
                min_length = min(min_length, i - dq.popleft())
            
            while dq and prefix_sums[i] <= prefix_sums[dq[-1]]:
                dq.pop()
            
            dq.append(i)
        
        return min_length if min_length != float('inf') else -1