# Source: https://leetcode.com/problems/minimum-number-of-operations-to-reinitialize-a-permutation/   |   Difficulty: Medium
#
# Problem Description:
# You are given an even integer n​​​​​​. You initially have a permutation perm of size n​​ where perm[i] == i​ (0-indexed)​​​​.
#
# In one operation, you will create a new array arr, and for each i:
#
#
# 	If i % 2 == 0, then arr[i] = perm[i / 2].
# 	If i % 2 == 1, then arr[i] = perm[n / 2 + (i - 1) / 2].
#
#
# You will then assign arr​​​​ to perm.
#
# Return the minimum non-zero number of operations you need to perform on perm to return the permutation to its initial value.
#
# Example:
# Input: n = 2
# Output: 1
# Explanation: perm = [0,1] initially.
# After the 1st operation, perm = [0,1]
# So it takes only 1 operation.
#
# Constraints:
# 2 <= n <= 1000
# 	n​​​​​​ is even.
#
# Helpful references (internal KB):
# - Gray code (number, simulation)
#   • When to use: Use when generating a sequence of numbers where adjacent values must differ by only one bit, or for error detection in digital systems. It is also useful for certain combinatorial problems.
#   • Idea: Gray code is a binary numeral system where two successive values differ in exactly one bit position. It can be generated efficiently using bitwise operations in O(1) time per code, or O(N) for N codes.
#   • Invariants: The number of bits in the generated Gray code G(n) is equal to the number of bits in the input binary n.; G(0) is always 0, and G(1) is always 1.
#   • Tips: The most common formula for converting binary n to Gray code G(n) is G(n) = n ^ (n >> 1).; To convert Gray code G(n) back to binary n, use a series of XOR operations: n = G(n) ^ (G(n) >> 1) ^ (G(n) >> 2) ^ ... until zero.
#   • Pitfalls: Confusing Gray code with standard binary representation, which can have multiple bit changes between successive numbers.; Incorrectly implementing the conversion formulas, especially the Gray to binary conversion.
# - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
#   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
#   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
#   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
#   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
#   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
# - Sqrt Tree (array, tree, divide-and-conquer, recursion, prefix-sum)
#   • When to use: When performing associative range queries on an array, especially when O(1) query time is critical and O(N log log N) preprocessing is acceptable.
#   • Idea: The Sqrt Tree is a data structure that answers associative range queries on an array in O(1) time after O(N log log N) preprocessing. It achieves this by recursively applying sqrt decomposition, precomputing block-wise prefix/suffix operations and inter-block results.
#   • Invariants: The `prefixOp` array for any block `k` stores the associative sum from the block's start to each element within it.; The `suffixOp` array for any block `k` stores the associative sum from each element within it to the block's end.
#   • Tips: Ensure the operation is strictly associative for correctness.; Carefully handle block boundaries and partial blocks during query processing.
#   • Pitfalls: Using non-associative operations will yield incorrect results.; High memory usage for the 'between' array if not optimized or if N is very large.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def reinitializePermutation(self, n):
        """
        :type n: int
        :rtype: int
        """
        count = 0
        i = 1
        while True:
            if i % 2 == 0:
                i //= 2
            else:
                i = n // 2 + (i - 1) // 2
            count += 1
            if i == 1:
                break
        return count