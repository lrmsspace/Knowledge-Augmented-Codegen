# Source: https://leetcode.com/problems/find-the-sum-of-the-power-of-all-subsequences/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums of length n and a positive integer k.
#
# The power of an array of integers is defined as the number of subsequences with their sum equal to k.
#
# Return the sum of power of all subsequences of nums.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input:   nums = [1,2,3], k = 3 
#
# Output:   6 
#
# Explanation:
#
# There are 5 subsequences of nums with non-zero power:
#
#
# 	The subsequence [1,2,3] has 2 subsequences with sum == 3: [1,2,3] and [1,2,3].
# 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
# 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
# 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
# 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
#
#
# Hence the answer is 2 + 1 + 1 + 1 + 1 = 6.
#
# Constraints:
# 1 <= n <= 100
# 	1 <= nums[i] <= 104
# 	1 <= k <= 100
#
# Helpful references (internal KB):
# - Binary Exponentiation by Factoring (number, counting, mod-exp)
#   • When to use: Use when performing modular exponentiation for an odd base modulo a power of two, especially when dealing with specific logarithmic-like functions or inverses in this modulus.
#   • Idea: This technique computes modular exponentiation for an odd base modulo a power of two by factoring the exponent or its inverse into a product of terms like (2^n+1). It leverages bit manipulation to efficiently find this factorization, allowing for O(d) or O(d log d) complexity where d is the exponent of the modulus.
#   • Invariants: During the iterative process to find $x^{-1} \pmod{2^d}$, the current value of $x$ is always odd.; After processing bit $n$, the $n$-th bit of the current $x$ (for $x^{-1}$ calculation) is zero, and lower bits are unchanged.
#   • Tips: Precompute $4L(2^n+1)$ values for efficiency.; Leverage bitwise operations for multiplying by $2^n+1$ (e.g., x = x + (x << n)).
#   • Pitfalls: This method is specific to odd bases and moduli of the form $2^d$; it's not a general modular exponentiation.; Careful handling of negative results from $4L(x^{-1})$ when working with modular arithmetic.
# - Modular Multiplicative Inverse (array, number, dp-1d)
#   • When to use: Use when division operations are required in modular arithmetic, especially for combinatorics or probability problems under a modulus. It's crucial for precomputing inverses efficiently for a range of numbers.
#   • Idea: Calculates the modular multiplicative inverse of a number 'a' modulo 'm', which is an integer 'x' such that (a * x) % m == 1. When precomputing inverses for a range [1, N], a linear time O(N) dynamic programming approach can be used.
#   • Invariants: For all k in [1, i-1], inv[k] correctly stores k^(-1) % m.; inv[i] is computed using previously calculated inv[m % i].
#   • Tips: For prime modulus 'm', a^(m-2) % m (Fermat's Little Theorem) is efficient for a single inverse.; The Extended Euclidean Algorithm works for any 'm' if gcd(a, m) = 1.
#   • Pitfalls: A modular inverse only exists if gcd(a, m) == 1.; Fermat's Little Theorem is only applicable when the modulus 'm' is prime.
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
    def sumOfPower(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        dp = [0] * (k + 1)
        dp[0] = 1  # Base case: one way to sum to 0 (empty subsequence)

        for num in nums:
            for j in range(k, num - 1, -1):
                dp[j] = (dp[j] + dp[j - num]) % MOD

        power_sum = 0
        for j in range(k + 1):
            power_sum = (power_sum + dp[j] * pow(2, n - dp[j], MOD)) % MOD

        return power_sum