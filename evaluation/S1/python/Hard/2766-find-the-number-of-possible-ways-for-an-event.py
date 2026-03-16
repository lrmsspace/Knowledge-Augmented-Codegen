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
# - Binomial Coefficients (array, number, mod-exp, enumeration)
#   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
#   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
#   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
#   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
#   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
# - Submask Enumeration
#  (number, bitset, enumeration, bitmask-dp)
#   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
#   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
#   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
#   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
#   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
# - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
#   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
#   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
#   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
#   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
#   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
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

        # Precompute factorials and inverse factorials for binomial coefficients
        MAXN = n + x  # Maximum value for n + x
        fact = [1] * (MAXN + 1)
        invFact = [1] * (MAXN + 1)

        for i in range(2, MAXN + 1):
            fact[i] = fact[i - 1] * i % MOD

        invFact[MAXN] = pow(fact[MAXN], MOD - 2, MOD)  # Fermat's little theorem for modular inverse
        for i in range(MAXN - 1, -1, -1):
            invFact[i] = invFact[i + 1] * (i + 1) % MOD

        def binomial(n, k):
            if k > n or k < 0:
                return 0
            return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD

        total_ways = 0
        # Iterate over the number of non-empty stages (bands)
        for k in range(1, min(n, x) + 1):
            # Ways to choose k stages from x
            choose_stages = binomial(x, k)
            # Ways to distribute n performers into k non-empty stages (Stirling numbers of the second kind)
            distribute_performers = binomial(n - 1, k - 1)
            # Ways to assign scores to k bands
            assign_scores = pow(y, k, MOD)

            total_ways += choose_stages * distribute_performers % MOD * assign_scores % MOD
            total_ways %= MOD

        return total_ways