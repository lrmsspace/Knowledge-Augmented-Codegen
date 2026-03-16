# Source: https://leetcode.com/problems/find-missing-observations/   |   Difficulty: Medium
#
# Problem Description:
# You have observations of n + m 6-sided dice rolls with each face numbered from 1 to 6. n of the observations went missing, and you only have the observations of m rolls. Fortunately, you have also calculated the average value of the n + m rolls.
#
# You are given an integer array rolls of length m where rolls[i] is the value of the ith observation. You are also given the two integers mean and n.
#
# Return an array of length n containing the missing observations such that the average value of the n + m rolls is exactly mean. If there are multiple valid answers, return any of them. If no such array exists, return an empty array.
#
# The average value of a set of k numbers is the sum of the numbers divided by k.
#
# Note that mean is an integer, so the sum of the n + m rolls should be divisible by n + m.
#
# Example:
# Input: rolls = [3,2,4,3], mean = 4, n = 2
# Output: [6,6]
# Explanation: The mean of all n + m rolls is (3 + 2 + 4 + 3 + 6 + 6) / 6 = 4.
#
# Constraints:
# m == rolls.length
# 	1 <= n, m <= 105
# 	1 <= rolls[i], mean <= 6
#
# Helpful references (internal KB):
# - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
#   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
#   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
#   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
#   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
#   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
# - Integer factorization (number, enumeration)
#   • When to use: Use when needing to decompose a composite integer into its prime factors, especially for numbers where trial division is feasible. It's suitable for problems requiring the unique prime components of a number.
#   • Idea: Integer factorization decomposes a given composite number into a product of its prime factors. The most common approach, trial division, involves testing divisibility by prime numbers up to the square root of the number, with optimizations for small primes and patterns like modulo 6.
#   • Invariants: The product of found prime factors multiplied by the current number equals the original number.; All prime factors found so far are less than or equal to the current trial divisor.
#   • Tips: Handle small prime factors (2, 3, 5) separately for efficiency.; Optimize trial division by checking only primes or numbers of form 6k +/- 1.
#   • Pitfalls: Forgetting to handle the case where the remaining number is a prime factor itself.; Inefficiently checking all numbers instead of only potential prime divisors.
# - Placing Bishops on a Chessboard (array, counting, dp-2d)
#   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
#   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
#   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
#   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
#   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def missingRolls(self, rolls, mean, n):
        """
        :type rolls: List[int]
        :type mean: int
        :type n: int
        :rtype: List[int]
        """
        m = len(rolls)
        total_sum = mean * (n + m)
        observed_sum = sum(rolls)
        missing_sum = total_sum - observed_sum

        if missing_sum < n or missing_sum > 6 * n:
            return []

        base_value = missing_sum // n
        remainder = missing_sum % n

        result = [base_value] * n
        for i in range(remainder):
            result[i] += 1

        return result