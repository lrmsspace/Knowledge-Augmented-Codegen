# Source: https://leetcode.com/problems/permutations-iv/   |   Difficulty: Hard
#
# Problem Description:
# Given two integers, n and k, an alternating permutation is a permutation of the first n positive integers such that no two adjacent elements are both odd or both even.
#
# Return the k-th alternating permutation sorted in lexicographical order. If there are fewer than k valid alternating permutations, return an empty list.
#
# Example:
# Input: n = 4, k = 6
#
# Output: [3,4,1,2]
#
# Explanation:
#
# The lexicographically-sorted alternating permutations of [1, 2, 3, 4] are:
#
#
# 	[1, 2, 3, 4]
# 	[1, 4, 3, 2]
# 	[2, 1, 4, 3]
# 	[2, 3, 4, 1]
# 	[3, 2, 1, 4]
# 	[3, 4, 1, 2] ← 6th permutation
# 	[4, 1, 2, 3]
# 	[4, 3, 2, 1]
#
#
# Since k = 6, we return [3, 4, 1, 2].
#
# Constraints:
# 1 <= n <= 100
# 	1 <= k <= 1015
#
# Helpful references (internal KB):
# - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
#   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
#   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
#   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
#   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
#   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
# - Placing Bishops on a Chessboard (array, counting, dp-2d)
#   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
#   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
#   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
#   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
#   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
# - Factorial modulo 
# p (number, counting, recursion)
#   • When to use: Use when the problem asks for the total count of possibilities or arrangements that can be naturally broken down into smaller, self-similar subproblems. It's effective for exploring decision trees or state spaces.
#   • Idea: Counting determines the number of elements or event occurrences. It uses combinatorial or iterative/recursive methods, often with O(N) or O(log N) complexity.
#   • Invariants: Each recursive call processes a smaller, well-defined subproblem.; The base cases correctly return the count for the simplest scenarios.
#   • Tips: Identify the smallest subproblem and its base cases to stop recursion.; Define the recursive relation clearly, showing how larger problems depend on smaller ones.
#   • Pitfalls: Incorrectly defining base cases can lead to infinite recursion or incorrect results.; Overlapping subproblems without memoization can lead to exponential time complexity.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def permute(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: List[int]
        """
        # Step 1: Generate all alternating permutations of [1, 2, ..., n]
        def is_alternating(perm):
            for i in range(len(perm) - 1):
                if (perm[i] % 2 == perm[i + 1] % 2):
                    return False
            return True

        from itertools import permutations
        all_perms = permutations(range(1, n + 1))
        alternating_perms = [perm for perm in all_perms if is_alternating(perm)]

        # Step 2: Sort the alternating permutations lexicographically
        alternating_perms.sort()

        # Step 3: Return the k-th permutation if it exists
        if k <= len(alternating_perms):
            return list(alternating_perms[k - 1])
        else:
            return []