# Source: https://leetcode.com/problems/count-the-number-of-ideal-arrays/   |   Difficulty: Hard
#
# Problem Description:
# You are given two integers n and maxValue, which are used to describe an ideal array.
#
# A 0-indexed integer array arr of length n is considered ideal if the following conditions hold:
#
#
# 	Every arr[i] is a value from 1 to maxValue, for 0 <= i < n.
# 	Every arr[i] is divisible by arr[i - 1], for 0 < i < n.
#
#
# Return the number of distinct ideal arrays of length n. Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: n = 2, maxValue = 5
# Output: 10
# Explanation: The following are the possible ideal arrays:
# - Arrays starting with the value 1 (5 arrays): [1,1], [1,2], [1,3], [1,4], [1,5]
# - Arrays starting with the value 2 (2 arrays): [2,2], [2,4]
# - Arrays starting with the value 3 (1 array): [3,3]
# - Arrays starting with the value 4 (1 array): [4,4]
# - Arrays starting with the value 5 (1 array): [5,5]
# There are a total of 5 + 2 + 1 + 1 + 1 = 10 distinct ideal arrays.
#
# Constraints:
# 2 <= n <= 104
# 	1 <= maxValue <= 104
#

class Solution(object):
    def idealArrays(self, n, maxValue):
        """
        :type n: int
        :type maxValue: int
        :rtype: int
        """
        MOD = 10**9 + 7

        # Precompute factorials and inverse factorials for combinations
        max_comb = n + 14  # since maxValue <= 10^4, the max number of prime factors is small
        fact = [1] * (max_comb + 1)
        inv_fact = [1] * (max_comb + 1)

        for i in range(2, max_comb + 1):
            fact[i] = fact[i - 1] * i % MOD

        inv_fact[max_comb] = pow(fact[max_comb], MOD - 2, MOD)
        for i in range(max_comb - 1, 0, -1):
            inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD

        def comb(a, b):
            if a < b or b < 0:
                return 0
            return fact[a] * inv_fact[b] % MOD * inv_fact[a - b] % MOD

        # Sieve to find prime factors
        spf = list(range(maxValue + 1))  # smallest prime factor
        for i in range(2, int(maxValue**0.5) + 1):
            if spf[i] == i:
                for j in range(i * i, maxValue + 1, i):
                    if spf[j] == j:
                        spf[j] = i

        def prime_factors_count(x):
            count = {}
            while x > 1:
                p = spf[x]
                count[p] = count.get(p, 0) + 1
                x //= p
            return count

        result = 0
        for val in range(1, maxValue + 1):
            pf_count = prime_factors_count(val)
            ways = 1
            for exp in pf_count.values():
                ways = ways * comb(n - 1 + exp, exp) % MOD
            result = (result + ways) % MOD

        return result