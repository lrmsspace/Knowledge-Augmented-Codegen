# Source: https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums and an integer k. You want to find a subsequence of nums of length k that has the largest sum.
#
# Return any such subsequence as an integer array of length k.
#
# A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
#
# Example:
# Input: nums = [2,1,3,3], k = 2
# Output: [3,3]
# Explanation:
# The subsequence has the largest sum of 3 + 3 = 6.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	-105 <= nums[i] <= 105
# 	1 <= k <= nums.length
#

class Solution(object):
    def maxSubsequence(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        indexed_nums = [(num, i) for i, num in enumerate(nums)]
        indexed_nums.sort(key=lambda x: x[0], reverse=True)
        top_k = sorted(indexed_nums[:k], key=lambda x: x[1])
        return [num for num, i in top_k]