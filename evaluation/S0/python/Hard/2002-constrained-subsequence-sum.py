# Source: https://leetcode.com/problems/constrained-subsequence-sum/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence of that array such that for every two consecutive integers in the subsequence, nums[i] and nums[j], where i < j, the condition j - i <= k is satisfied.
#
# A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array, leaving the remaining elements in their original order.
#
# Example:
# Input: nums = [10,2,-10,5,20], k = 2
# Output: 37
# Explanation: The subsequence is [10, 2, 5, 20].
#
# Constraints:
# 1 <= k <= nums.length <= 105
# 	-104 <= nums[i] <= 104
#

class Solution(object):
    def constrainedSubsetSum(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from collections import deque

        n = len(nums)
        dp = [0] * n
        dp[0] = nums[0]
        max_deque = deque([0])  # Store indices of potential max dp values

        for i in range(1, n):
            # Remove indices that are out of the k range
            while max_deque and max_deque[0] < i - k:
                max_deque.popleft()

            # Calculate dp[i]
            dp[i] = nums[i] + max(0, dp[max_deque[0]])

            # Maintain the deque to keep it decreasing
            while max_deque and dp[max_deque[-1]] <= dp[i]:
                max_deque.pop()
            max_deque.append(i)

        return max(dp)