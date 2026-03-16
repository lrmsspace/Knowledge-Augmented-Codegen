# Source: https://leetcode.com/problems/minimum-bit-flips-to-convert-number/   |   Difficulty: Easy
#
# Problem Description:
# A bit flip of a number x is choosing a bit in the binary representation of x and flipping it from either 0 to 1 or 1 to 0.
#
#
# 	For example, for x = 7, the binary representation is 111 and we may choose any bit (including any leading zeros not shown) and flip it. We can flip the first bit from the right to get 110, flip the second bit from the right to get 101, flip the fifth bit from the right (a leading zero) to get 10111, etc.
#
#
# Given two integers start and goal, return the minimum number of bit flips to convert start to goal.
#
# Example:
# Input: start = 10, goal = 7
# Output: 3
# Explanation: The binary representation of 10 and 7 are 1010 and 0111 respectively. We can convert 10 to 7 in 3 steps:
# - Flip the first bit from the right: 1010 -> 1011.
# - Flip the third bit from the right: 1011 -> 1111.
# - Flip the fourth bit from the right: 1111 -> 0111.
# It can be shown we cannot convert 10 to 7 in less than 3 steps. Hence, we return 3.
#
# Constraints:
# 0 <= start, goal <= 109
#
#
#  
# Note: This question is the same as 461: Hamming Distance.
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
# - Bit manipulation (number, simulation)
#   • When to use: Use when operations on individual bits of an integer are required, for optimizing arithmetic with powers of two, or for efficient management of boolean flags.
#   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators and shifts. These operations typically have O(1) time complexity as they are hardware-level instructions.
#   • Invariants: The total number of bits representing the integer remains constant for fixed-width types.; Applying `n & (1 << k)` isolates the k-th bit, setting all other bits to zero.
#   • Tips: Use `&` with `(1 << k)` to check if the k-th bit is set.; Use `|` with `(1 << k)` to set the k-th bit.
#   • Pitfalls: Be aware of integer overflow when performing large left shifts.; Understand the difference between arithmetic and logical right shifts, especially for signed numbers.
# - Binary Exponentiation by Factoring (number, mod-exp, enumeration)
#   • When to use: Used to solve discrete logarithm problems of the form g^x = y mod m, specifically when the modulus m is a power of 2. It iteratively determines the bits of the exponent x.
#   • Idea: It solves the discrete logarithm problem g^x = y mod m by iteratively determining the bits of x, specifically optimized for moduli that are powers of 2. The approach involves modular exponentiation and inverse operations, typically resulting in a complexity of O(log^2 m) or O(log m) depending on modular inverse efficiency.
#   • Invariants: After k steps, the k least significant bits of x are correctly identified.; The current effective target y' is congruent to g^(2^k * x_remaining) modulo 2^d.
#   • Tips: Carefully handle modular arithmetic with powers of 2, as properties differ from prime moduli.; The order of g modulo 2^d is crucial for determining the number of bits to recover.
#   • Pitfalls: Incorrectly calculating modular inverses for non-coprime numbers with 2^d.; Off-by-one errors when determining the number of squaring steps.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minBitFlips(self, start, goal):
        """
        :type start: int
        :type goal: int
        :rtype: int
        """
        xor = start ^ goal
        count = 0
        while xor:
            count += xor & 1
            xor >>= 1
        return count