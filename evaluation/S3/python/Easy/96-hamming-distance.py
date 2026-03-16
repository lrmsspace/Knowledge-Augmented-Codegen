# Source: https://leetcode.com/problems/hamming-distance/   |   Difficulty: Easy
#
# Problem Description:
# The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
#
# Given two integers x and y, return the Hamming distance between them.
#
# Example:
# Input: x = 1, y = 4
# Output: 2
# Explanation:
# 1   (0 0 0 1)
# 4   (0 1 0 0)
#        ↑   ↑
# The above arrows point to positions where the corresponding bits are different.
#
# Constraints:
# 0 <= x, y <= 231 - 1
#
#
#  
# Note: This question is the same as  2220: Minimum Bit Flips to Convert Number.
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Gray code (number, prefix-xor)
#   • When to use: Use when a sequence of binary numbers is needed where successive values differ by only one bit. This is useful for error detection in digital systems or position encoders.
#   • Idea: Gray code is a binary numeral system where two successive values differ in only one bit position. Conversion from a binary number `n` to its Gray code `G(n)` is `n ^ (n >> 1)`, and the inverse operation can also be performed efficiently in O(log N) time.
#   • Invariants: For binary to Gray: The resulting Gray code `G(n)` differs from `n` by exactly one bit for each `n`.; For inverse Gray to binary: The variable `n` accumulates the correct binary value from MSB to LSB.
#   • Tips: Understand the core `n ^ (n >> 1)` transformation for binary to Gray.; The inverse Gray code conversion involves iteratively XORing with right-shifted values.
#   • Pitfalls: Confusing Gray code with standard binary representation.; Incorrectly implementing the iterative inverse transformation logic.
# - Bit manipulation (number, enumeration, simulation)
#   • When to use: When problems involve manipulating individual bits of numbers, representing sets as bitmasks, or optimizing operations on powers of two. It is also useful for certain combinatorics and dynamic programming problems.
#   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators. This technique is often used to optimize computations, manage boolean flags efficiently, or represent subsets, typically achieving O(1) complexity for fixed-size integers.
#   • Invariants: Each bit in the mask accurately reflects the inclusion or exclusion status of its corresponding element.; Bitwise operations maintain the integrity of unaffected bits.
#   • Tips: Use (1 << k) to create a mask with the k-th bit set.; n & (n-1) clears the least significant set bit.
#   • Pitfalls: Incorrect operator precedence can lead to subtle bugs.; Mixing signed and unsigned integers in bitwise operations can yield unexpected results.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def hammingDistance(self, x, y):
        """
        :type x: int
        :type y: int
        :rtype: int
        """
        # XOR of x and y will give a number with bits set to 1 where x and y differ
        xor = x ^ y
        
        # Count the number of set bits in xor
        distance = 0
        while xor:
            distance += xor & 1  # Increment distance if the least significant bit is 1
            xor >>= 1  # Right shift to check the next bit
        
        return distance