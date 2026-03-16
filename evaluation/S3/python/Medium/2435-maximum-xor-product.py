# Source: https://leetcode.com/problems/maximum-xor-product/   |   Difficulty: Medium
#
# Problem Description:
# Given three integers a, b, and n, return the maximum value of (a XOR x) * (b XOR x) where 0 <= x < 2n.
#
# Since the answer may be too large, return it modulo 109 + 7.
#
# Note that XOR is the bitwise XOR operation.
#
# Example:
# Input: a = 12, b = 5, n = 4
# Output: 98
# Explanation: For x = 2, (a XOR x) = 14 and (b XOR x) = 7. Hence, (a XOR x) * (b XOR x) = 98. 
# It can be shown that 98 is the maximum value of (a XOR x) * (b XOR x) for all 0 <= x < 2n.
#
# Constraints:
# 0 <= a, b < 250
# 	0 <= n <= 50
#
# Helpful references (internal KB):
# - Gray code (number, prefix-xor)
#   • When to use: Use when a sequence of binary numbers is needed where successive values differ by only one bit. This is useful for error detection in digital systems or position encoders.
#   • Idea: Gray code is a binary numeral system where two successive values differ in only one bit position. Conversion from a binary number `n` to its Gray code `G(n)` is `n ^ (n >> 1)`, and the inverse operation can also be performed efficiently in O(log N) time.
#   • Invariants: For binary to Gray: The resulting Gray code `G(n)` differs from `n` by exactly one bit for each `n`.; For inverse Gray to binary: The variable `n` accumulates the correct binary value from MSB to LSB.
#   • Tips: Understand the core `n ^ (n >> 1)` transformation for binary to Gray.; The inverse Gray code conversion involves iteratively XORing with right-shifted values.
#   • Pitfalls: Confusing Gray code with standard binary representation.; Incorrectly implementing the iterative inverse transformation logic.
# - Gray code (number, simulation)
#   • When to use: Use when generating a sequence of numbers where adjacent values must differ by only one bit, or for error detection in digital systems. It is also useful for certain combinatorial problems.
#   • Idea: Gray code is a binary numeral system where two successive values differ in exactly one bit position. It can be generated efficiently using bitwise operations in O(1) time per code, or O(N) for N codes.
#   • Invariants: The number of bits in the generated Gray code G(n) is equal to the number of bits in the input binary n.; G(0) is always 0, and G(1) is always 1.
#   • Tips: The most common formula for converting binary n to Gray code G(n) is G(n) = n ^ (n >> 1).; To convert Gray code G(n) back to binary n, use a series of XOR operations: n = G(n) ^ (G(n) >> 1) ^ (G(n) >> 2) ^ ... until zero.
#   • Pitfalls: Confusing Gray code with standard binary representation, which can have multiple bit changes between successive numbers.; Incorrectly implementing the conversion formulas, especially the Gray to binary conversion.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumXorProduct(self, a, b, n):
        """
        :type a: int
        :type b: int
        :type n: int
        :rtype: int
        """
        MOD = 10**9 + 7
        max_x = (1 << n) - 1
        max_product = 0

        for x in range(max_x + 1):
            product = (a ^ x) * (b ^ x)
            max_product = max(max_product, product)

        return max_product % MOD