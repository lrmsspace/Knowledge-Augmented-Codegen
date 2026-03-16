# Source: https://leetcode.com/problems/special-permutations/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums containing n distinct positive integers. A permutation of nums is called special if:
#
#
# 	For all indexes 0 <= i < n - 1, either nums[i] % nums[i+1] == 0 or nums[i+1] % nums[i] == 0.
#
#
# Return the total number of special permutations. As the answer could be large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [2,3,6]
# Output: 2
# Explanation: [3,6,2] and [2,6,3] are the two special permutations of nums.
#
# Constraints:
# 2 <= nums.length <= 14
# 	1 <= nums[i] <= 109
#

class Solution(object):
    def specialPerm(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        full_mask = (1 << n) - 1

        # Precompute divisibility
        div = [[False] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if i != j:
                    div[i][j] = (nums[i] % nums[j] == 0 or nums[j] % nums[i] == 0)

        # DP table
        dp = [[0] * n for _ in range(1 << n)]

        # Base case: single element permutations
        for i in range(n):
            dp[1 << i][i] = 1

        # Fill DP table
        for mask in range(1 << n):
            for last in range(n):
                if not (mask & (1 << last)):
                    continue
                for nxt in range(n):
                    if mask & (1 << nxt):
                        continue
                    if div[last][nxt]:
                        dp[mask | (1 << nxt)][nxt] = (dp[mask | (1 << nxt)][nxt] + dp[mask][last]) % MOD

        # Sum up all permutations that use all elements
        result = sum(dp[full_mask][i] for i in range(n)) % MOD
        return result