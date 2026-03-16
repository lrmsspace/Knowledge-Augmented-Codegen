# Source: https://leetcode.com/problems/number-of-longest-increasing-subsequence/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, return the number of longest increasing subsequences.
#
# Notice that the sequence has to be strictly increasing.
#
# Example:
# Input: nums = [1,3,5,4,7]
# Output: 2
# Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].
#
# Constraints:
# 1 <= nums.length <= 2000
# 	-106 <= nums[i] <= 106
# 	The answer is guaranteed to fit inside a 32-bit integer.
#

class Solution(object):
    def findNumberOfLIS(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        if n == 0:
            return 0
        
        lengths = [1] * n  # lengths[i] = length of longest ending in nums[i]
        counts = [1] * n   # counts[i] = number of longest ending in nums[i]
        
        for i in range(n):
            for j in range(i):
                if nums[i] > nums[j]:
                    if lengths[j] + 1 > lengths[i]:
                        lengths[i] = lengths[j] + 1
                        counts[i] = counts[j]
                    elif lengths[j] + 1 == lengths[i]:
                        counts[i] += counts[j]
        
        longest = max(lengths)
        return sum(c for l, c in zip(lengths, counts) if l == longest)