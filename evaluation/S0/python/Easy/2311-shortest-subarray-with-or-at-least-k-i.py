# Source: https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-i/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array nums of non-negative integers and an integer k.
#
# An array is called special if the bitwise OR of all of its elements is at least k.
#
# Return the length of the shortest special non-empty subarray of nums, or return -1 if no special subarray exists.
#
# Example:
# Input: nums = [1,2,3], k = 2
#
# Output: 1
#
# Explanation:
#
# The subarray [3] has OR value of 3. Hence, we return 1.
#
# Note that [2] is also a special subarray.
#
# Constraints:
# 1 <= nums.length <= 50
# 	0 <= nums[i] <= 50
# 	0 <= k < 64
#

class Solution(object):
    def minimumSubarrayLength(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        min_length = float('inf')
        
        for i in range(n):
            current_or = 0
            for j in range(i, n):
                current_or |= nums[j]
                if current_or >= k:
                    min_length = min(min_length, j - i + 1)
                    break
        
        return min_length if min_length != float('inf') else -1