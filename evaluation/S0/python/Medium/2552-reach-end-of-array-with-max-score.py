# Source: https://leetcode.com/problems/reach-end-of-array-with-max-score/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums of length n.
#
# Your goal is to start at index 0 and reach index n - 1. You can only jump to indices greater than your current index.
#
# The score for a jump from index i to index j is calculated as (j - i) * nums[i].
#
# Return the maximum possible total score by the time you reach the last index.
#
# Example:
# Input: nums = [1,3,1,5]
#
# Output: 7
#
# Explanation:
#
# First, jump to index 1 and then jump to the last index. The final score is 1 * 1 + 2 * 3 = 7.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 105
#

class Solution(object):
    def findMaximumScore(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        dp = [0] * n
        dp[0] = 0

        for i in range(1, n):
            max_score = 0
            for j in range(i):
                score = (i - j) * nums[j] + dp[j]
                if score > max_score:
                    max_score = score
            dp[i] = max_score

        return dp[-1]