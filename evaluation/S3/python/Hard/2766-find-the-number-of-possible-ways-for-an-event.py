# Source: https://leetcode.com/problems/find-the-number-of-possible-ways-for-an-event/   |   Difficulty: Hard
#
# Problem Description:
# You are given three integers n, x, and y.
#
# An event is being held for n performers. When a performer arrives, they are assigned to one of the x stages. All performers assigned to the same stage will perform together as a band, though some stages might remain empty.
#
# After all performances are completed, the jury will award each band a score in the range [1, y].
#
# Return the total number of possible ways the event can take place.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Note that two events are considered to have been held differently if either of the following conditions is satisfied:
#
#
# 	Any performer is assigned a different stage.
# 	Any band is awarded a different score.
#
# Example:
# Input: n = 1, x = 2, y = 3
#
# Output: 6
#
# Explanation:
#
#
# 	There are 2 ways to assign a stage to the performer.
# 	The jury can award a score of either 1, 2, or 3 to the only band.
#
# Constraints:
# 1 <= n, x, y <= 1000
#
# Helpful references (internal KB):
# - Binomial Coefficients (array, dp-2d)
#   • When to use: Use when you need to compute many binomial coefficients, especially for values up to a certain N, or when working with modulo arithmetic where division is not straightforward.
#   • Idea: This method computes binomial coefficients using Pascal's identity, building a 2D DP table where C(n, k) = C(n-1, k-1) + C(n-1, k). It has a time complexity of O(N^2) for computing all coefficients up to N.
#   • Invariants: For each cell dp[i][j], it stores the value of C(i, j).; At the start of computing row i, all values for row i-1 are correctly calculated and available.
#   • Tips: Optimize space by storing only the current and previous row of the DP table.; For O(1) lookup after precomputation, calculate all factorials and inverse factorials modulo a prime.
#   • Pitfalls: Direct division for C(n,k) = n! / (k!(n-k)!) is problematic with modulo arithmetic unless the modulo is prime.; Integer overflow can occur for large N and K if not handled with appropriate data types or modulo operations.
# - Binomial Coefficients (array, enumeration)
#   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
#   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
#   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
#   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
#   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
# - Binomial Coefficients (array, number, dp-1d, mod-exp)
#   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
#   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
#   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
#   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
#   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfWays(self, n, x, y):
        """
        :type n: int
        :type x: int
        :type y: int
        :rtype: int
        """
        MOD = 10**9 + 7

        # Step 1: Calculate the number of ways to assign n performers to x stages
        # This is equivalent to counting the number of ways to distribute n indistinguishable items (performers) into x distinguishable boxes (stages).
        # The formula for this is C(n + x - 1, x - 1) = (n + x - 1)! / (n! * (x - 1)!)
        
        # Step 2: Calculate the number of ways to assign scores to the bands
        # The number of bands is equal to the number of non-empty stages, which can be at most min(n, x).
        # Each band can receive a score from 1 to y, so if there are k bands, there are y^k ways to assign scores.

        # We will iterate over the possible number of non-empty stages (bands) from 1 to min(n, x)
        total_ways = 0
        for k in range(1, min(n, x) + 1):
            # Calculate C(n + x - 1, x - 1) for k non-empty stages
            if k > n:
                break
            ways_to_assign_stages = self.binomial_coefficient(n + k - 1, k - 1, MOD)
            ways_to_assign_scores = pow(y, k, MOD)
            total_ways = (total_ways + ways_to_assign_stages * ways_to_assign_scores) % MOD

        return total_ways