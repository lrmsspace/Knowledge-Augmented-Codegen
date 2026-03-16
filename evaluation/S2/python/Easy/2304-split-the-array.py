# Source: https://leetcode.com/problems/split-the-array/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums of even length. You have to split the array into two parts nums1 and nums2 such that:
#
#
# 	nums1.length == nums2.length == nums.length / 2.
# 	nums1 should contain distinct elements.
# 	nums2 should also contain distinct elements.
#
#
# Return true if it is possible to split the array, and false otherwise.
#
# Example:
# Input: nums = [1,1,2,2,3,4]
# Output: true
# Explanation: One of the possible ways to split nums is nums1 = [1,2,3] and nums2 = [1,2,4].
#
# Constraints:
# 1 <= nums.length <= 100
# 	nums.length % 2 == 0 
# 	1 <= nums[i] <= 100
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isPossibleToSplit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        n = len(nums)
        unique_nums = set(nums)
        return len(unique_nums) >= n // 2