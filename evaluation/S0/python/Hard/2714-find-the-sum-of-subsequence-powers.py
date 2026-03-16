# Source: https://leetcode.com/problems/find-the-sum-of-subsequence-powers/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums of length n, and a positive integer k.
#
# The power of a subsequence is defined as the minimum absolute difference between any two elements in the subsequence.
#
# Return the sum of powers of all subsequences of nums which have length equal to k.
#
# Since the answer may be large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [1,2,3,4], k = 3
#
# Output: 4
#
# Explanation:
#
# There are 4 subsequences in nums which have length 3: [1,2,3], [1,3,4], [1,2,4], and [2,3,4]. The sum of powers is |2 - 3| + |3 - 4| + |2 - 1| + |3 - 4| = 4.
#
# Constraints:
# 2 <= n == nums.length <= 50
# 	-108 <= nums[i] <= 108 
# 	2 <= k <= n
#

class Solution(object):
    def sumOfPowers(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        nums.sort()
        
        # Precompute factorials and inverse factorials for combinations
        fact = [1] * (n + 1)
        inv_fact = [1] * (n + 1)
        
        for i in range(2, n + 1):
            fact[i] = fact[i - 1] * i % MOD
        
        inv_fact[n] = pow(fact[n], MOD - 2, MOD)
        for i in range(n - 1, 0, -1):
            inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD
        
        def comb(a, b):
            if b > a or b < 0:
                return 0
            return fact[a] * inv_fact[b] % MOD * inv_fact[a - b] % MOD
        
        total_power = 0
        
        for i in range(n):
            for j in range(i + 1, n):
                diff = nums[j] - nums[i]
                count = comb(j - i - 1, k - 2)
                total_power = (total_power + diff * count) % MOD
        
        return total_power