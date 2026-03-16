# Source: https://leetcode.com/problems/minimize-or-of-remaining-elements-using-operations/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array nums and an integer k.
#
# In one operation, you can pick any index i of nums such that 0 <= i < nums.length - 1 and replace nums[i] and nums[i + 1] with a single occurrence of nums[i] & nums[i + 1], where & represents the bitwise AND operator.
#
# Return the minimum possible value of the bitwise OR of the remaining elements of nums after applying at most k operations.
#
# Example:
# Input: nums = [3,5,3,2,7], k = 2
# Output: 3
# Explanation: Let's do the following operations:
# 1. Replace nums[0] and nums[1] with (nums[0] & nums[1]) so that nums becomes equal to [1,3,2,7].
# 2. Replace nums[2] and nums[3] with (nums[2] & nums[3]) so that nums becomes equal to [1,3,2].
# The bitwise-or of the final array is 3.
# It can be shown that 3 is the minimum possible value of the bitwise OR of the remaining elements of nums after applying at most k operations.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] < 230
# 	0 <= k < nums.length
#

class Solution(object):
    def minOrAfterOperations(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        INF = (1 << 31) - 1
        
        # dp[i][j]: Minimum OR value for first i elements with j operations
        dp = [[INF] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 0
        
        for i in range(1, n + 1):
            for j in range(k + 1):
                # No operation on the i-th element
                dp[i][j] = min(dp[i][j], dp[i - 1][j] | nums[i - 1])
                
                # Perform operation on the last two elements if possible
                if j > 0 and i >= 2:
                    combined = nums[i - 2] & nums[i - 1]
                    dp[i][j] = min(dp[i][j], dp[i - 2][j - 1] | combined)
        
        return min(dp[n][j] for j in range(k + 1))