# Source: https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer array nums and an integer k, find three non-overlapping subarrays of length k with maximum sum and return them.
#
# Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.
#
# Example:
# Input: nums = [1,2,1,2,6,7,5,1], k = 2
# Output: [0,3,5]
# Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
# We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
#
# Constraints:
# 1 <= nums.length <= 2 * 104
# 	1 <= nums[i] < 216
# 	1 <= k <= floor(nums.length / 3)
#

class Solution(object):
    def maxSumOfThreeSubarrays(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        n = len(nums)
        W = [0] * (n - k + 1)
        curr_sum = sum(nums[:k])
        W[0] = curr_sum
        for i in range(1, n - k + 1):
            curr_sum += nums[i + k - 1] - nums[i - 1]
            W[i] = curr_sum

        left = [0] * len(W)
        best = 0
        for i in range(len(W)):
            if W[i] > W[best]:
                best = i
            left[i] = best

        right = [0] * len(W)
        best = len(W) - 1
        for i in range(len(W) - 1, -1, -1):
            if W[i] >= W[best]:
                best = i
            right[i] = best

        ans = None
        for j in range(k, len(W) - k):
            i, l = left[j - k], right[j + k]
            if ans is None or W[i] + W[j] + W[l] > W[ans[0]] + W[ans[1]] + W[ans[2]]:
                ans = [i, j, l]

        return ans