# Source: https://leetcode.com/problems/double-modular-exponentiation/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed 2D array variables where variables[i] = [ai, bi, ci, mi], and an integer target.
#
# An index i is good if the following formula holds:
#
#
# 	0 <= i < variables.length
# 	((aibi % 10)ci) % mi == target
#
#
# Return an array consisting of good indices in any order.
#
# Example:
# Input: variables = [[2,3,3,10],[3,3,3,1],[6,1,1,4]], target = 2
# Output: [0,2]
# Explanation: For each index i in the variables array:
# 1) For the index 0, variables[0] = [2,3,3,10], (23 % 10)3 % 10 = 2.
# 2) For the index 1, variables[1] = [3,3,3,1], (33 % 10)3 % 1 = 0.
# 3) For the index 2, variables[2] = [6,1,1,4], (61 % 10)1 % 4 = 2.
# Therefore we return [0,2] as the answer.
#
# Constraints:
# 1 <= variables.length <= 100
# 	variables[i] == [ai, bi, ci, mi]
# 	1 <= ai, bi, ci, mi <= 103
# 	0 <= target <= 103
#
# Helpful references (internal KB):
# - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
#   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
#   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
#   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
#   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
#   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
# - Binary Exponentiation by Factoring (number, mod-exp, enumeration)
#   • When to use: Used to solve discrete logarithm problems of the form g^x = y mod m, specifically when the modulus m is a power of 2. It iteratively determines the bits of the exponent x.
#   • Idea: It solves the discrete logarithm problem g^x = y mod m by iteratively determining the bits of x, specifically optimized for moduli that are powers of 2. The approach involves modular exponentiation and inverse operations, typically resulting in a complexity of O(log^2 m) or O(log m) depending on modular inverse efficiency.
#   • Invariants: After k steps, the k least significant bits of x are correctly identified.; The current effective target y' is congruent to g^(2^k * x_remaining) modulo 2^d.
#   • Tips: Carefully handle modular arithmetic with powers of 2, as properties differ from prime moduli.; The order of g modulo 2^d is crucial for determining the number of bits to recover.
#   • Pitfalls: Incorrectly calculating modular inverses for non-coprime numbers with 2^d.; Off-by-one errors when determining the number of squaring steps.
# - Binomial Coefficients (array, number, mod-exp, enumeration)
#   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
#   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
#   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
#   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
#   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getGoodIndices(self, variables, target):
        """
        :type variables: List[List[int]]
        :type target: int
        :rtype: List[int]
        """
        result = []
        for i, (a, b, c, m) in enumerate(variables):
            mod_exp = pow(pow(a, b, 10), c, m)
            if mod_exp == target:
                result.append(i)
        return result