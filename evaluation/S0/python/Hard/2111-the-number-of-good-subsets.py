# Source: https://leetcode.com/problems/the-number-of-good-subsets/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums. We call a subset of nums good if its product can be represented as a product of one or more distinct prime numbers.
#
#
# 	For example, if nums = [1, 2, 3, 4]:
#
# 	
# 		[2, 3], [1, 2, 3], and [1, 3] are good subsets with products 6 = 2*3, 6 = 2*3, and 3 = 3 respectively.
# 		[1, 4] and [4] are not good subsets with products 4 = 2*2 and 4 = 2*2 respectively.
# 	
# 	
#
#
# Return the number of different good subsets in nums modulo 109 + 7.
#
# A subset of nums is any array that can be obtained by deleting some (possibly none or all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
#
# Example:
# Input: nums = [1,2,3,4]
# Output: 6
# Explanation: The good subsets are:
# - [1,2]: product is 2, which is the product of distinct prime 2.
# - [1,2,3]: product is 6, which is the product of distinct primes 2 and 3.
# - [1,3]: product is 3, which is the product of distinct prime 3.
# - [2]: product is 2, which is the product of distinct prime 2.
# - [2,3]: product is 6, which is the product of distinct primes 2 and 3.
# - [3]: product is 3, which is the product of distinct prime 3.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 30
#

class Solution(object):
    def numberOfGoodSubsets(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        primes = [2,3,5,7,11,13,17,19,23,29]
        prime_to_bit = {p: i for i, p in enumerate(primes)}
        
        count = [0] * 31
        for num in nums:
            count[num] += 1
        
        dp = [0] * (1 << len(primes))
        dp[0] = 1
        
        for num in range(2, 31):
            if count[num] == 0:
                continue
            
            subset_mask = 0
            temp = num
            valid = True
            
            for p in primes:
                if temp % (p * p) == 0:
                    valid = False
                    break
                if temp % p == 0:
                    subset_mask |= (1 << prime_to_bit[p])
                    temp //= p
            
            if not valid:
                continue
            
            for mask in range((1 << len(primes)) - 1, -1, -1):
                if (mask & subset_mask) == 0:
                    dp[mask | subset_mask] = (dp[mask | subset_mask] + dp[mask] * count[num]) % MOD
        
        result = sum(dp[1:]) % MOD
        result = (result * pow(2, count[1], MOD)) % MOD
        
        return result