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
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
# - Binomial Coefficients (array, dp-2d)
#   • When to use: Use when you need to compute many binomial coefficients, especially for values up to a certain N, or when working with modulo arithmetic where division is not straightforward.
#   • Idea: This method computes binomial coefficients using Pascal's identity, building a 2D DP table where C(n, k) = C(n-1, k-1) + C(n-1, k). It has a time complexity of O(N^2) for computing all coefficients up to N.
#   • Invariants: For each cell dp[i][j], it stores the value of C(i, j).; At the start of computing row i, all values for row i-1 are correctly calculated and available.
#   • Tips: Optimize space by storing only the current and previous row of the DP table.; For O(1) lookup after precomputation, calculate all factorials and inverse factorials modulo a prime.
#   • Pitfalls: Direct division for C(n,k) = n! / (k!(n-k)!) is problematic with modulo arithmetic unless the modulo is prime.; Integer overflow can occur for large N and K if not handled with appropriate data types or modulo operations.
# - Modular Multiplicative Inverse (array, number, dp-1d)
#   • When to use: Use when division operations are required in modular arithmetic, especially for combinatorics or probability problems under a modulus. It's crucial for precomputing inverses efficiently for a range of numbers.
#   • Idea: Calculates the modular multiplicative inverse of a number 'a' modulo 'm', which is an integer 'x' such that (a * x) % m == 1. When precomputing inverses for a range [1, N], a linear time O(N) dynamic programming approach can be used.
#   • Invariants: For all k in [1, i-1], inv[k] correctly stores k^(-1) % m.; inv[i] is computed using previously calculated inv[m % i].
#   • Tips: For prime modulus 'm', a^(m-2) % m (Fermat's Little Theorem) is efficient for a single inverse.; The Extended Euclidean Algorithm works for any 'm' if gcd(a, m) = 1.
#   • Pitfalls: A modular inverse only exists if gcd(a, m) == 1.; Fermat's Little Theorem is only applicable when the modulus 'm' is prime.
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
        
        # dp[i][j][l] = number of arrays of length i, max element j, with search cost l
        dp = [[[0] * (k + 1) for _ in range(m + 1)] for _ in range(n + 1)]
        
        # Base case: one array of length 0 with max element 0 and search cost 0
        dp[0][0][0] = 1
        
        for i in range(1, n + 1):
            for j in range(1, m + 1):
                for l in range(k + 1):
                    # Case 1: last element is less than current max j
                    dp[i][j][l] += dp[i - 1][j][l] * (j - 1)
                    dp[i][j][l] %= MOD
                    
                    # Case 2: last element is equal to current max j
                    if l > 0:
                        dp[i][j][l] += dp[i - 1][j - 1][l - 1]
                        dp[i][j][l] %= MOD
        
        # Sum up all arrays of length n with any max element and search cost k
        result = sum(dp[n][j][k] for j in range(1, m + 1)) % MOD
        return result