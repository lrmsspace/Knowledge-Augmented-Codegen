# Source: https://leetcode.com/problems/find-the-maximum-length-of-a-good-subsequence-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and a non-negative integer k. A sequence of integers seq is called good if there are at most k indices i in the range [0, seq.length - 2] such that seq[i] != seq[i + 1].
#
# Return the maximum possible length of a good subsequence of nums.
#
# Example:
# Input: nums = [1,2,1,1,3], k = 2
#
# Output: 4
#
# Explanation:
#
# The maximum length subsequence is [1,2,1,1,3].
#
# Constraints:
# 1 <= nums.length <= 500
# 	1 <= nums[i] <= 109
# 	0 <= k <= min(nums.length, 25)
#

class Solution(object):
    def maximumLength(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from collections import Counter
        count = Counter(nums)
        max_freq = max(count.values())
        n = len(nums)
        return min(n, max_freq + 2 * k)