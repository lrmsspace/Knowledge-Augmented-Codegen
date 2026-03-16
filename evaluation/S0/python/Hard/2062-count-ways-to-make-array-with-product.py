# Source: https://leetcode.com/problems/count-ways-to-make-array-with-product/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D integer array, queries. For each queries[i], where queries[i] = [ni, ki], find the number of different ways you can place positive integers into an array of size ni such that the product of the integers is ki. As the number of ways may be too large, the answer to the ith query is the number of ways modulo 109 + 7.
#
# Return an integer array answer where answer.length == queries.length, and answer[i] is the answer to the ith query.
#
# Example:
# Input: queries = [[2,6],[5,1],[73,660]]
# Output: [4,1,50734910]
# Explanation: Each query is independent.
# [2,6]: There are 4 ways to fill an array of size 2 that multiply to 6: [1,6], [2,3], [3,2], [6,1].
# [5,1]: There is 1 way to fill an array of size 5 that multiply to 1: [1,1,1,1,1].
# [73,660]: There are 1050734917 ways to fill an array of size 73 that multiply to 660. 1050734917 modulo 109 + 7 = 50734910.
#
# Constraints:
# 1 <= queries.length <= 104 
# 	1 <= ni, ki <= 104
#

class Solution(object):
    def waysToFillArray(self, queries):
        """
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        MOD = 10**9 + 7
        
        # Precompute factorials and inverse factorials for combinations
        max_n = 20000
        fact = [1] * (max_n + 1)
        inv_fact = [1] * (max_n + 1)
        
        for i in range(2, max_n + 1):
            fact[i] = fact[i - 1] * i % MOD
        
        inv_fact[max_n] = pow(fact[max_n], MOD - 2, MOD)
        for i in range(max_n - 1, 0, -1):
            inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD
        
        def comb(n, k):
            if k > n or k < 0:
                return 0
            return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD
        
        def prime_factors_count(k):
            count = {}
            d = 2
            while d * d <= k:
                while (k % d) == 0:
                    if d in count:
                        count[d] += 1
                    else:
                        count[d] = 1
                    k //= d
                d += 1
            if k > 1:
                count[k] = 1
            return count
        
        results = []
        for n, k in queries:
            factors = prime_factors_count(k)
            ways = 1
            for exp in factors.values():
                ways = ways * comb(n + exp - 1, exp) % MOD
            results.append(ways)
        
        return results