# Source: https://leetcode.com/problems/count-good-numbers/   |   Difficulty: Medium
#
# Problem Description:
# A digit string is good if the digits (0-indexed) at even indices are even and the digits at odd indices are prime (2, 3, 5, or 7).
#
#
# 	For example, "2582" is good because the digits (2 and 8) at even positions are even and the digits (5 and 2) at odd positions are prime. However, "3245" is not good because 3 is at an even index but is not even.
#
#
# Given an integer n, return the total number of good digit strings of length n. Since the answer may be large, return it modulo 109 + 7.
#
# A digit string is a string consisting of digits 0 through 9 that may contain leading zeros.
#
# Example:
# Input: n = 1
# Output: 5
# Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".
#
# Constraints:
# 1 <= n <= 1015
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Binomial Coefficients (array, number, mod-exp, enumeration)
#   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
#   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
#   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
#   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
#   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
# - Chinese Remainder Theorem (number, mod-exp)
#   • When to use: Used to find an integer that satisfies a system of multiple congruence relations, particularly when the moduli are pairwise coprime. It's essential for reconstructing numbers from their remainders.
#   • Idea: The Chinese Remainder Theorem finds a unique integer solution to a system of linear congruences, modulo the product of their pairwise coprime moduli. It iteratively combines congruences, often using the Extended Euclidean Algorithm for modular inverses, with a complexity polynomial in the number of congruences.
#   • Invariants: The current combined solution satisfies all previously processed congruences.; The current combined modulus is the product of all previously processed pairwise coprime moduli.
#   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Use the Extended Euclidean Algorithm to find modular inverses.
#   • Pitfalls: Forgetting to check if moduli are pairwise coprime, leading to no unique solution or no solution.; Incorrectly calculating modular inverses, which is crucial for the algorithm.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countGoodNumbers(self, n):
        """
        :type n: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        even_positions = (n + 1) // 2
        odd_positions = n // 2
        
        # Calculate 5^even_positions % MOD
        even_count = pow(5, even_positions, MOD)
        # Calculate 4^odd_positions % MOD
        odd_count = pow(4, odd_positions, MOD)
        
        return (even_count * odd_count) % MOD