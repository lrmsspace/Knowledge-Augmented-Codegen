# Source: https://leetcode.com/problems/count-the-number-of-infection-sequences/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n and an array sick sorted in increasing order, representing positions of infected people in a line of n people.
#
# At each step, one uninfected person adjacent to an infected person gets infected. This process continues until everyone is infected.
#
# An infection sequence is the order in which uninfected people become infected, excluding those initially infected.
#
# Return the number of different infection sequences possible, modulo 109+7.
#
# Example:
# Input: n = 5, sick = [0,4]
#
# Output: 4
#
# Explanation:
#
# There is a total of 6 different sequences overall.
#
#
# 	Valid infection sequences are [1,2,3], [1,3,2], [3,2,1] and [3,1,2].
# 	[2,3,1] and [2,1,3] are not valid infection sequences because the person at index 2 cannot be infected at the first step.
#
# Constraints:
# 2 <= n <= 105
# 	1 <= sick.length <= n - 1
# 	0 <= sick[i] <= n - 1
# 	sick is sorted in increasing order.
#
# Helpful references (internal KB):
# - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
#   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
#   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
#   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
#   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
#   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
# - Binomial Coefficients (array, number, mod-exp, enumeration)
#   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
#   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
#   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
#   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
#   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
# - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
#   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
#   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
#   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
#   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
#   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfSequence(self, n, sick):
        """
        :type n: int
        :type sick: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        m = len(sick)
        dp = [[0] * (m + 1) for _ in range(n - m + 1)]
        dp[0][0] = 1

        for i in range(1, n - m + 1):
            for j in range(0, min(i, m) + 1):
                if j > 0:
                    dp[i][j] += dp[i - 1][j - 1] * (m - (j - 1))
                if j < m:
                    dp[i][j] += dp[i - 1][j] * (i - (j))
                dp[i][j] %= MOD

        return dp[n - m][m]