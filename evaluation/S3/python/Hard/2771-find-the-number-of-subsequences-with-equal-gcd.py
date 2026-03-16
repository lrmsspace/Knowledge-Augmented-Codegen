# Source: https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums.
#
# Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:
#
#
# 	The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
# 	The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
#
#
# Return the total number of such pairs.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [1,2,3,4]
#
# Output: 10
#
# Explanation:
#
# The subsequence pairs which have the GCD of their elements equal to 1 are:
#
#
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
#
# Constraints:
# 1 <= nums.length <= 200
# 	1 <= nums[i] <= 200
#
# Helpful references (internal KB):
# - Binomial Coefficients (array, number, dp-1d, mod-exp)
#   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
#   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
#   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
#   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
#   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
# - Binomial Coefficients (array, dp-2d)
#   • When to use: Use when you need to compute many binomial coefficients, especially for values up to a certain N, or when working with modulo arithmetic where division is not straightforward.
#   • Idea: This method computes binomial coefficients using Pascal's identity, building a 2D DP table where C(n, k) = C(n-1, k-1) + C(n-1, k). It has a time complexity of O(N^2) for computing all coefficients up to N.
#   • Invariants: For each cell dp[i][j], it stores the value of C(i, j).; At the start of computing row i, all values for row i-1 are correctly calculated and available.
#   • Tips: Optimize space by storing only the current and previous row of the DP table.; For O(1) lookup after precomputation, calculate all factorials and inverse factorials modulo a prime.
#   • Pitfalls: Direct division for C(n,k) = n! / (k!(n-k)!) is problematic with modulo arithmetic unless the modulo is prime.; Integer overflow can occur for large N and K if not handled with appropriate data types or modulo operations.
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
    def subsequencePairCount(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from math import gcd
        from collections import defaultdict

        MOD = 10**9 + 7
        max_num = max(nums)
        
        # Count frequency of each number in nums
        freq = [0] * (max_num + 1)
        for num in nums:
            freq[num] += 1
        
        # Count subsequences with GCD equal to g
        count_gcd = [0] * (max_num + 1)
        
        for g in range(1, max_num + 1):
            # Count how many numbers are multiples of g
            multiples_count = sum(freq[i] for i in range(g, max_num + 1, g))
            if multiples_count > 0:
                count_gcd[g] = pow(2, multiples_count, MOD) - 1
        
        # Inclusion-Exclusion to find exact GCD counts
        for g in range(max_num, 0, -1):
            for multiple in range(2 * g, max_num + 1, g):
                count_gcd[g] = (count_gcd[g] - count_gcd[multiple]) % MOD
        
        # Calculate the number of valid pairs
        result = 0
        for g in range(1, max_num + 1):
            if count_gcd[g] > 0:
                result = (result + count_gcd[g] * count_gcd[g]) % MOD
        
        return result