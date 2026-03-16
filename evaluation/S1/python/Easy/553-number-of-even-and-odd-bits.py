# Source: https://leetcode.com/problems/number-of-even-and-odd-bits/   |   Difficulty: Easy
#
# Problem Description:
# You are given a positive integer n.
#
# Let even denote the number of even indices in the binary representation of n with value 1.
#
# Let odd denote the number of odd indices in the binary representation of n with value 1.
#
# Note that bits are indexed from right to left in the binary representation of a number.
#
# Return the array [even, odd].
#
# Example:
# Input: n = 50
#
# Output: [1,2]
#
# Explanation:
#
# The binary representation of 50 is 110010.
#
# It contains 1 on indices 1, 4, and 5.
#
# Constraints:
# 1 <= n <= 1000
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Binary Exponentiation by Factoring (number, counting, mod-exp)
#   • When to use: Use when performing modular exponentiation for an odd base modulo a power of two, especially when dealing with specific logarithmic-like functions or inverses in this modulus.
#   • Idea: This technique computes modular exponentiation for an odd base modulo a power of two by factoring the exponent or its inverse into a product of terms like (2^n+1). It leverages bit manipulation to efficiently find this factorization, allowing for O(d) or O(d log d) complexity where d is the exponent of the modulus.
#   • Invariants: During the iterative process to find $x^{-1} \pmod{2^d}$, the current value of $x$ is always odd.; After processing bit $n$, the $n$-th bit of the current $x$ (for $x^{-1}$ calculation) is zero, and lower bits are unchanged.
#   • Tips: Precompute $4L(2^n+1)$ values for efficiency.; Leverage bitwise operations for multiplying by $2^n+1$ (e.g., x = x + (x << n)).
#   • Pitfalls: This method is specific to odd bases and moduli of the form $2^d$; it's not a general modular exponentiation.; Careful handling of negative results from $4L(x^{-1})$ when working with modular arithmetic.
# - Submask Enumeration
#  (number, bitset, enumeration, bitmask-dp)
#   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
#   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
#   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
#   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
#   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def evenOddBit(self, n):
        """
        :type n: int
        :rtype: List[int]
        """
        even = 0
        odd = 0
        index = 0
        
        while n > 0:
            if n & 1:
                if index % 2 == 0:
                    even += 1
                else:
                    odd += 1
            n >>= 1
            index += 1
        
        return [even, odd]