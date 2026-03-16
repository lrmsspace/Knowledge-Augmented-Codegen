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
# Helpful references (internal KB):
# - The Inclusion-Exclusion Principle (array, number, counting, sieve)
#   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
#   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
#   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
#   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
#   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
# - Stars and bars (number, counting)
#   • When to use: Use when counting the number of ways to distribute identical items into distinct bins, or finding the number of non-negative or positive integer solutions to a linear equation of sums.
#   • Idea: A combinatorial technique to count the number of ways to distribute 'n' identical items into 'k' distinct bins, or find integer solutions to x1 + ... + xk = n.
#   • Invariants: The total number of 'stars' (items) remains constant throughout the distribution.; The number of 'bars' (dividers, k-1) remains constant, separating the k distinct bins.
#   • Tips: Distinguish between non-negative (xi >= 0) and positive (xi >= 1) integer solutions; the latter requires a variable transformation.; For positive integer solutions (xi >= 1), transform variables to yi = xi - 1, then solve for yi >= 0 with a reduced sum.
#   • Pitfalls: Confusing identical items/distinct bins with distinct items/distinct bins (which is k^n).; Incorrectly applying the formula for positive vs. non-negative constraints without transformation.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def distributeCandies(self, n, limit):
        """
        :type n: int
        :type limit: int
        :rtype: int
        """
        MOD = 10**9 + 7

        def modinv(a, p):
            return pow(a, p - 2, p)

        def nCr(n, r, p):
            if r > n or r < 0:
                return 0
            numerator = 1
            for i in range(r):
                numerator = (numerator * (n - i)) % p
            denominator = 1
            for i in range(1, r + 1):
                denominator = (denominator * i) % p
            return (numerator * modinv(denominator, p)) % p

        total_ways = nCr(n + 3 - 1, 3 - 1, MOD)

        subtract_ways = 0
        for i in range(1, 4):
            ways = nCr(n - i * (limit + 1) + 3 - 1, 3 - 1, MOD)
            if i % 2 == 1:
                subtract_ways = (subtract_ways + ways) % MOD
            else:
                subtract_ways = (subtract_ways - ways + MOD) % MOD

        result = (total_ways - subtract_ways + MOD) % MOD
        return result