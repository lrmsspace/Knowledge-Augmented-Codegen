# Source: https://leetcode.com/problems/1-bit-and-2-bit-characters/   |   Difficulty: Easy
#
# Problem Description:
# We have two special characters:
#
#
# 	The first character can be represented by one bit 0.
# 	The second character can be represented by two bits (10 or 11).
#
#
# Given a binary array bits that ends with 0, return true if the last character must be a one-bit character.
#
# Example:
# Input: bits = [1,0,0]
# Output: true
# Explanation: The only way to decode it is two-bit character and one-bit character.
# So the last character is one-bit character.
#
# Constraints:
# 1 <= bits.length <= 1000
# 	bits[i] is either 0 or 1.
#
# Helpful references (internal KB):
# - Bit manipulation (number, simulation)
#   • When to use: Use when operations on individual bits of an integer are required, for optimizing arithmetic with powers of two, or for efficient management of boolean flags.
#   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators and shifts. These operations typically have O(1) time complexity as they are hardware-level instructions.
#   • Invariants: The total number of bits representing the integer remains constant for fixed-width types.; Applying `n & (1 << k)` isolates the k-th bit, setting all other bits to zero.
#   • Tips: Use `&` with `(1 << k)` to check if the k-th bit is set.; Use `|` with `(1 << k)` to set the k-th bit.
#   • Pitfalls: Be aware of integer overflow when performing large left shifts.; Understand the difference between arithmetic and logical right shifts, especially for signed numbers.
# - Longest increasing subsequence (array, dp-1d, binary-search)
#   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
#   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
#   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
#   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
#   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
# - Gray code (number, simulation)
#   • When to use: Use when generating a sequence of numbers where adjacent values must differ by only one bit, or for error detection in digital systems. It is also useful for certain combinatorial problems.
#   • Idea: Gray code is a binary numeral system where two successive values differ in exactly one bit position. It can be generated efficiently using bitwise operations in O(1) time per code, or O(N) for N codes.
#   • Invariants: The number of bits in the generated Gray code G(n) is equal to the number of bits in the input binary n.; G(0) is always 0, and G(1) is always 1.
#   • Tips: The most common formula for converting binary n to Gray code G(n) is G(n) = n ^ (n >> 1).; To convert Gray code G(n) back to binary n, use a series of XOR operations: n = G(n) ^ (G(n) >> 1) ^ (G(n) >> 2) ^ ... until zero.
#   • Pitfalls: Confusing Gray code with standard binary representation, which can have multiple bit changes between successive numbers.; Incorrectly implementing the conversion formulas, especially the Gray to binary conversion.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isOneBitCharacter(self, bits):
        """
        :type bits: List[int]
        :rtype: bool
        """
        i = 0
        n = len(bits)
        
        while i < n - 1:  # We only need to check up to the second last bit
            if bits[i] == 1:
                i += 2  # Two-bit character
            else:
                i += 1  # One-bit character
        
        # If we end up at the last index, it's a one-bit character
        return i == n - 1