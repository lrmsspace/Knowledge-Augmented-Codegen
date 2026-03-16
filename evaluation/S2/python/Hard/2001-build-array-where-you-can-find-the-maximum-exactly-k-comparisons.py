# Source: https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/   |   Difficulty: Hard
#
# Problem Description:
# You are given three integers n, m and k. Consider the following algorithm to find the maximum element of an array of positive integers:
#
# You should build the array arr which has the following properties:
#
#
# 	arr has exactly n integers.
# 	1 <= arr[i] <= m where (0 <= i < n).
# 	After applying the mentioned algorithm to arr, the value search_cost is equal to k.
#
#
# Return the number of ways to build the array arr under the mentioned conditions. As the answer may grow large, the answer must be computed modulo 109 + 7.
#
# Example:
# Input: n = 2, m = 3, k = 1
# Output: 6
# Explanation: The possible arrays are [1, 1], [2, 1], [2, 2], [3, 1], [3, 2] [3, 3]
#
# Constraints:
# 1 <= n <= 50
# 	1 <= m <= 100
# 	0 <= k <= n
#
# Helpful references (internal KB):
# - Binomial Coefficients (array, number, dp-1d, mod-exp)
#   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
#   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
#   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
#   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
#   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Josephus Problem (number, simulation, recursion)
#   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
#   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
#   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
#   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
#   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numOfArrays(self, n, m, k):
        """
        :type n: int
        :type m: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        # dp[i][j][l] = number of arrays of length i, max element j, and search cost l
        dp = [[[0] * (k + 1) for _ in range(m + 1)] for _ in range(n + 1)]
        
        # Base case: For length 1, max element j, search cost is 0
        for j in range(1, m + 1):
            dp[1][j][0] = 1
        
        for i in range(2, n + 1):
            for j in range(1, m + 1):
                for l in range(k + 1):
                    # Case 1: The new element is less than or equal to the current max j
                    dp[i][j][l] = (dp[i][j][l] + dp[i - 1][j][l] * j) % MOD
                    
                    # Case 2: The new element is greater than the current max j
                    if l > 0:
                        dp[i][j][l] = (dp[i][j][l] + sum(dp[i - 1][x][l - 1] for x in range(1, j)) * (m - j + 1)) % MOD
        
        return sum(dp[n][j][k] for j in range(1, m + 1)) % MOD