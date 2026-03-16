# Source: https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/   |   Difficulty: Hard
#
# Problem Description:
# You are given two 0-indexed integer arrays nums and multipliers of size n and m respectively, where n >= m.
#
# You begin with a score of 0. You want to perform exactly m operations. On the ith operation (0-indexed) you will:
#
#
#     Choose one integer x from either the start or the end of the array nums.
#     Add multipliers[i] * x to your score.
#     
#         Note that multipliers[0] corresponds to the first operation, multipliers[1] to the second operation, and so on.
#     
#     
#     Remove x from nums.
#
#
# Return the maximum score after performing m operations.
#
# Example:
# Input: nums = [1,2,3], multipliers = [3,2,1]
# Output: 14
# Explanation: An optimal solution is as follows:
# - Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
# - Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
# - Choose from the end, [1], adding 1 * 1 = 1 to the score.
# The total score is 9 + 4 + 1 = 14.
#
# Constraints:
# n == nums.length
# 	m == multipliers.length
# 	1 <= m <= 300
# 	m <= n <= 105 
# 	-1000 <= nums[i], multipliers[i] <= 1000
#

class Solution(object):
    def maximumScore(self, nums, multipliers):
        """
        :type nums: List[int]
        :type multipliers: List[int]
        :rtype: int
        """
        n = len(nums)
        m = len(multipliers)
        dp = [[0] * (m + 1) for _ in range(m + 1)]

        for i in range(m - 1, -1, -1):
            for left in range(i, -1, -1):
                mult = multipliers[i]
                right = n - 1 - (i - left)
                dp[left][i - left] = max(
                    mult * nums[left] + dp[left + 1][i - left],
                    mult * nums[right] + dp[left][i - left + 1]
                )

        return dp[0][0]