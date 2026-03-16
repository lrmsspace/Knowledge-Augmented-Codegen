# Source: https://leetcode.com/problems/count-the-number-of-inversions/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n and a 2D array requirements, where requirements[i] = [endi, cnti] represents the end index and the inversion count of each requirement.
#
# A pair of indices (i, j) from an integer array nums is called an inversion if:
#
#
# 	i < j and nums[i] > nums[j]
#
#
# Return the number of permutations perm of [0, 1, 2, ..., n - 1] such that for all requirements[i], perm[0..endi] has exactly cnti inversions.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: n = 3, requirements = [[2,2],[0,0]]
#
# Output: 2
#
# Explanation:
#
# The two permutations are:
#
#
# 	[2, 0, 1]
#
# 	
# 		Prefix [2, 0, 1] has inversions (0, 1) and (0, 2).
# 		Prefix [2] has 0 inversions.
# 	
# 	
# 	[1, 2, 0]
# 	
# 		Prefix [1, 2, 0] has inversions (0, 2) and (1, 2).
# 		Prefix [1] has 0 inversions.
#
# Constraints:
# 2 <= n <= 300
# 	1 <= requirements.length <= n
# 	requirements[i] = [endi, cnti]
# 	0 <= endi <= n - 1
# 	0 <= cnti <= 400
# 	The input is generated such that there is at least one i such that endi == n - 1.
# 	The input is generated such that all endi are unique.
#

class Solution(object):
    def numberOfPermutations(self, n, requirements):
        """
        :type n: int
        :type requirements: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        max_inv = n * (n - 1) // 2
        
        dp = [[0] * (max_inv + 1) for _ in range(n + 1)]
        dp[0][0] = 1
        
        for i in range(1, n + 1):
            for j in range(max_inv + 1):
                dp[i][j] = dp[i][j - 1] + dp[i - 1][j]
                if j >= i:
                    dp[i][j] -= dp[i - 1][j - i]
                dp[i][j] %= MOD
        
        requirements.sort()
        prev_end, prev_count = -1, 0
        result = 1
        
        for endi, cnti in requirements:
            length = endi - prev_end
            count_diff = cnti - prev_count
            
            if count_diff < 0 or count_diff > length * (length - 1) // 2:
                return 0
            
            total_ways = dp[length][count_diff]
            result = (result * total_ways) % MOD
            
            prev_end, prev_count = endi, cnti
        
        return result