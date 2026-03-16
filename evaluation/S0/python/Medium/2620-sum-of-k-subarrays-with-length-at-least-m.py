# Source: https://leetcode.com/problems/sum-of-k-subarrays-with-length-at-least-m/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and two integers, k and m.
#
# Return the maximum sum of k non-overlapping subarrays of nums, where each subarray has a length of at least m.
#
# Example:
# Input: nums = [1,2,-1,3,3,4], k = 2, m = 2
#
# Output: 13
#
# Explanation:
#
# The optimal choice is:
#
#
# 	Subarray nums[3..5] with sum 3 + 3 + 4 = 10 (length is 3 >= m).
# 	Subarray nums[0..1] with sum 1 + 2 = 3 (length is 2 >= m).
#
#
# The total sum is 10 + 3 = 13.
#
# Constraints:
# 1 <= nums.length <= 2000
# 	-104 <= nums[i] <= 104
# 	1 <= k <= floor(nums.length / m)
# 	1 <= m <= 3
#

class Solution(object):
    def maxSum(self, nums, k, m):
        """
        :type nums: List[int]
        :type k: int
        :type m: int
        :rtype: int
        """
        n = len(nums)
        prefix_sum = [0] * (n + 1)
        
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + nums[i]
        
        dp = [[float('-inf')] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 0
        
        for i in range(1, n + 1):
            for j in range(k + 1):
                dp[i][j] = dp[i - 1][j]
                
                if j > 0:
                    for length in range(m, i + 1):
                        dp[i][j] = max(dp[i][j], dp[i - length][j - 1] + prefix_sum[i] - prefix_sum[i - length])
        
        return dp[n][k]