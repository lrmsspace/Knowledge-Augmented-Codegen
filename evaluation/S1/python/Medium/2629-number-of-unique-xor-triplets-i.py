# Source: https://leetcode.com/problems/number-of-unique-xor-triplets-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums of length n, where nums is a permutation of the numbers in the range [1, n].
#
# A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.
#
# Return the number of unique XOR triplet values from all possible triplets (i, j, k).
#
# Example:
# Input: nums = [1,2]
#
# Output: 2
#
# Explanation:
#
# The possible XOR triplet values are:
#
#
# 	(0, 0, 0) → 1 XOR 1 XOR 1 = 1
# 	(0, 0, 1) → 1 XOR 1 XOR 2 = 2
# 	(0, 1, 1) → 1 XOR 2 XOR 2 = 1
# 	(1, 1, 1) → 2 XOR 2 XOR 2 = 2
#
#
# The unique XOR values are {1, 2}, so the output is 2.
#
# Constraints:
# 1 <= n == nums.length <= 105
# 	1 <= nums[i] <= n
# 	nums is a permutation of integers from 1 to n.
#
# Helpful references (internal KB):
# - Fast Fourier transform (number, array, mod-exp)
#   • When to use: Use when you need to perform polynomial multiplication or convolution efficiently for large inputs, or when dealing with modular arithmetic for exact integer results.
#   • Idea: The Fast Fourier Transform (FFT) is an algorithm that computes the Discrete Fourier Transform (DFT) and its inverse in O(N log N) time. It efficiently transforms a sequence of values from the time domain to the frequency domain, enabling fast polynomial multiplication and convolution.
#   • Invariants: After each stage k, all sub-problems of size 2^k have their DFTs computed correctly.; The bit-reversal permutation ensures elements are in their correct final positions before butterfly operations begin.
#   • Tips: Precompute bit-reversal permutation for repeated calls with the same input size N.; Precompute roots of unity and their powers to optimize calculations.
#   • Pitfalls: Rounding errors can occur with standard FFT when dealing with large numbers or precision-sensitive calculations.; Incorrect implementation of the bit-reversal permutation can lead to wrong results.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Stars and bars (number, counting)
#   • When to use: Use when counting the number of ways to distribute identical items into distinct bins, or finding the number of non-negative integer solutions to a linear equation. It is also applicable for problems with lower bounds on variables.
#   • Idea: Stars and bars is a combinatorial technique used to count the number of ways to place 'n' identical items into 'k' distinct bins, or equivalently, to find the number of non-negative integer solutions to x1 + ... + xk = n.
#   • Invariants: The total number of 'stars' (items) remains constant throughout any transformation.; The number of 'bars' (separators) is always one less than the number of bins (variables).
#   • Tips: Visualize items as 'stars' and separators as 'bars' to understand the arrangement.; Transform problems with lower bounds (x_i >= a_i) into non-negative solutions (x_i' >= 0).
#   • Pitfalls: Confusing identical items with distinct items, which requires a different counting method.; Incorrectly applying the formula when variables have lower bounds other than zero without transformation.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def uniqueXorTriplets(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        prefix_xor = [0] * (n + 1)
        for i in range(n):
            prefix_xor[i + 1] = prefix_xor[i] ^ nums[i]

        unique_xors = set()
        for i in range(n):
            for j in range(i, n):
                xor_value = prefix_xor[i] ^ prefix_xor[j + 1]
                unique_xors.add(xor_value)

        return len(unique_xors)