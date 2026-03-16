# Source: https://leetcode.com/problems/distribute-candies-among-children-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given two positive integers n and limit.
#
# Return the total number of ways to distribute n candies among 3 children such that no child gets more than limit candies.
#
# Example:
# Input: n = 5, limit = 2
# Output: 3
# Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).
#
# Constraints:
# 1 <= n <= 106
# 	1 <= limit <= 106
#

class Solution(object):
    def distributeCandies(self, n, limit):
        """
        :type n: int
        :type limit: int
        :rtype: int
        """
        MOD = 10**9 + 7

        # Helper function to calculate nCr % MOD using Fermat's Little Theorem
        def nCr_mod(n, r):
            if r > n or r < 0:
                return 0
            numerator = 1
            denominator = 1
            for i in range(r):
                numerator = (numerator * (n - i)) % MOD
                denominator = (denominator * (i + 1)) % MOD
            return (numerator * pow(denominator, MOD - 2, MOD)) % MOD

        total_ways = nCr_mod(n + 3 - 1, 3 - 1)

        # Inclusion-Exclusion principle to subtract invalid distributions
        for i in range(1, 4):
            ways = nCr_mod(3, i) * nCr_mod(n - i * (limit + 1) + 3 - 1, 3 - 1)
            if i % 2 == 1:
                total_ways = (total_ways - ways + MOD) % MOD
            else:
                total_ways = (total_ways + ways) % MOD

        return total_ways