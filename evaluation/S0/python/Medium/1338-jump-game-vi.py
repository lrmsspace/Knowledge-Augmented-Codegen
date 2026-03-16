# Source: https://leetcode.com/problems/jump-game-vi/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums and an integer k.
#
# You are initially standing at index 0. In one move, you can jump at most k steps forward without going outside the boundaries of the array. That is, you can jump from index i to any index in the range [i + 1, min(n - 1, i + k)] inclusive.
#
# You want to reach the last index of the array (index n - 1). Your score is the sum of all nums[j] for each index j you visited in the array.
#
# Return the maximum score you can get.
#
# Example:
# Input: nums = [1,-1,-2,4,-7,3], k = 2
# Output: 7
# Explanation: You can choose your jumps forming the subsequence [1,-1,4,3] (underlined above). The sum is 7.
#
# Constraints:
# 1 <= nums.length, k <= 105
# 	-104 <= nums[i] <= 104
#

class Solution(object):
    def maxResult(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from collections import deque

        n = len(nums)
        dp = [0] * n
        dp[0] = nums[0]
        deq = deque([0])  # stores indices of nums array

        for i in range(1, n):
            # Remove indices that are out of the current window
            while deq and deq[0] < i - k:
                deq.popleft()

            # The current dp[i] is the sum of nums[i] and the maximum dp value within the window
            dp[i] = dp[deq[0]] + nums[i]

            # Maintain the deque to keep it decreasing
            while deq and dp[deq[-1]] <= dp[i]:
                deq.pop()
            deq.append(i)

        return dp[-1]