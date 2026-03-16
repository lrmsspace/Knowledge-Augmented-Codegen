# Source: https://leetcode.com/problems/number-of-unique-good-subsequences/   |   Difficulty: Hard
#
# Problem Description:
# You are given a binary string binary. A subsequence of binary is considered good if it is not empty and has no leading zeros (with the exception of "0").
#
# Find the number of unique good subsequences of binary.
#
#
# 	For example, if binary = "001", then all the good subsequences are ["0", "0", "1"], so the unique good subsequences are "0" and "1". Note that subsequences "00", "01", and "001" are not good because they have leading zeros.
#
#
# Return the number of unique good subsequences of binary. Since the answer may be very large, return it modulo 109 + 7.
#
# A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.
#
# Example:
# Input: binary = "001"
# Output: 2
# Explanation: The good subsequences of binary are ["0", "0", "1"].
# The unique good subsequences are "0" and "1".
#
# Constraints:
# 1 <= binary.length <= 105
# 	binary consists of only '0's and '1's.
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Factorial modulo 
# p (number, array, recursion, mod-exp, dp-1d)
#   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
#   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
#   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
#   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
#   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfUniqueGoodSubsequences(self, binary):
        """
        :type binary: str
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(binary)
        dp = [0] * (n + 1)  # dp[i] will store the count of unique good subsequences in binary[:i]
        dp[0] = 1  # Base case: there's one subsequence of an empty string (the empty subsequence)

        for i in range(1, n + 1):
            dp[i] = (dp[i - 1] * 2) % MOD  # Each subsequence can either include or exclude the new character
            if binary[i - 1] == '0':
                dp[i] = (dp[i] - dp[i - 1]) % MOD  # Remove subsequences that would have leading zeros

        # Subtract 1 to exclude the empty subsequence and add back 1 if '0' is present to count it as a valid subsequence
        return (dp[n] - 1 + (1 if '0' in binary else 0)) % MOD