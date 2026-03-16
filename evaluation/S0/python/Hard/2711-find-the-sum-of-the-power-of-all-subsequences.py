# Source: https://leetcode.com/problems/find-the-sum-of-the-power-of-all-subsequences/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums of length n and a positive integer k.
#
# The power of an array of integers is defined as the number of subsequences with their sum equal to k.
#
# Return the sum of power of all subsequences of nums.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input:   nums = [1,2,3], k = 3 
#
# Output:   6 
#
# Explanation:
#
# There are 5 subsequences of nums with non-zero power:
#
#
# 	The subsequence [1,2,3] has 2 subsequences with sum == 3: [1,2,3] and [1,2,3].
# 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
# 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
# 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
# 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
#
#
# Hence the answer is 2 + 1 + 1 + 1 + 1 = 6.
#
# Constraints:
# 1 <= n <= 100
# 	1 <= nums[i] <= 104
# 	1 <= k <= 100
#

class Solution(object):
    def sumOfPower(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        
        # dp[i][j]: number of subsequences using first i elements with sum j
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 1  # empty subsequence
        
        for i in range(1, n + 1):
            for j in range(k + 1):
                dp[i][j] = dp[i - 1][j]  # not include nums[i-1]
                if j >= nums[i - 1]:
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - nums[i - 1]]) % MOD
        
        total_power = 0
        for i in range(1, n + 1):
            total_power = (total_power + dp[i][k]) % MOD
        
        return total_power