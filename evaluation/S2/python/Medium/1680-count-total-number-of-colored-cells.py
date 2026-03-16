# Source: https://leetcode.com/problems/count-total-number-of-colored-cells/   |   Difficulty: Medium
#
# Problem Description:
# There exists an infinitely large two-dimensional grid of uncolored unit cells. You are given a positive integer n, indicating that you must do the following routine for n minutes:
#
#
# 	At the first minute, color any arbitrary unit cell blue.
# 	Every minute thereafter, color blue every uncolored cell that touches a blue cell.
#
#
# Below is a pictorial representation of the state of the grid after minutes 1, 2, and 3.
#
# Return the number of colored cells at the end of n minutes.
#
# Example:
# Input: n = 1
# Output: 1
# Explanation: After 1 minute, there is only 1 blue cell, so we return 1.
#
# Constraints:
# 1 <= n <= 105
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
#   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
#   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
#   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
#   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
#   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
# - Fibonacci Numbers (matrix, matrix-exp)
#   • When to use: Use when needing to compute the N-th Fibonacci number or similar linear recurrence relations for very large N efficiently, typically in logarithmic time.
#   • Idea: This method computes the N-th Fibonacci number by transforming the linear recurrence into a matrix multiplication, then using binary exponentiation (matrix exponentiation) to raise the transformation matrix to the N-th power. It achieves O(log N) time complexity.
#   • Invariants: The base matrix M = [[1, 1], [1, 0]] correctly transforms (F_k, F_{k-1}) to (F_{k+1}, F_k).; After k matrix multiplications, the accumulated matrix represents M^k.
#   • Tips: Understand binary exponentiation for matrices to efficiently compute powers.; The base transformation matrix for Fibonacci is typically [[1, 1], [1, 0]].
#   • Pitfalls: Incorrectly setting up the base matrix or initial vector.; Forgetting to apply modulo operations, leading to integer overflow for large numbers.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def coloredCells(self, n):
        """
        :type n: int
        :rtype: int
        """
        # The number of colored cells after n minutes can be expressed as a quadratic function of n.
        # Specifically, the pattern of colored cells forms a diamond shape that expands outward from the initial cell.
        # The formula for the number of colored cells after n minutes is:
        # Total colored cells = 2 * n * (n - 1) + 1
        # This accounts for the initial cell and the expansion in all four directions.
        
        return 2 * n * (n - 1) + 1