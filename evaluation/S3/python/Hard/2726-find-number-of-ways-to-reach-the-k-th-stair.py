# Source: https://leetcode.com/problems/find-number-of-ways-to-reach-the-k-th-stair/   |   Difficulty: Hard
#
# Problem Description:
# You are given a non-negative integer k. There exists a staircase with an infinite number of stairs, with the lowest stair numbered 0.
#
# Alice has an integer jump, with an initial value of 0. She starts on stair 1 and wants to reach stair k using any number of operations. If she is on stair i, in one operation she can:
#
#
# 	Go down to stair i - 1. This operation cannot be used consecutively or on stair 0.
# 	Go up to stair i + 2jump. And then, jump becomes jump + 1.
#
#
# Return the total number of ways Alice can reach stair k.
#
# Note that it is possible that Alice reaches the stair k, and performs some operations to reach the stair k again.
#
# Example:
# Input: k = 0
#
# Output: 2
#
# Explanation:
#
# The 2 possible ways of reaching stair 0 are:
#
#
# 	Alice starts at stair 1.
# 	
# 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
# 	
# 	
# 	Alice starts at stair 1.
# 	
# 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
# 		Using an operation of the second type, she goes up 20 stairs to reach stair 1.
# 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
#
# Constraints:
# 0 <= k <= 109
#
# Helpful references (internal KB):
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
#   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
#   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
#   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
#   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
#   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
# - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
#   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
#   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
#   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
#   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
#   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def waysToReachStair(self, k):
        """
        :type k: int
        :rtype: int
        """
        # 1. Alice starts at stair 1, so we can treat stair 1 as the starting point.
        # 2. The operations allow Alice to either go down (which cannot be used consecutively or on stair 0) or go up (which increases the jump count).
        # 3. We can use dynamic programming to count the number of ways to reach each stair from the starting point.
        # 4. We need to consider the constraints and ensure that we do not exceed the allowed operations.

        # Let's define a DP array where dp[i][j] represents the number of ways to reach stair i with j jumps.
        # The maximum number of jumps needed to reach stair k can be estimated based on the operations.

        max_jumps = 0
        while (1 << max_jumps) - 1 < k:  # Calculate maximum jumps needed
            max_jumps += 1

        dp = [[0] * (max_jumps + 1) for _ in range(k + 1)]
        dp[1][0] = 1  # Starting point

        for i in range(2, k + 1):
            for j in range(max_jumps + 1):
                if j > 0:
                    dp[i][j] += dp[i - (1 << (j - 1))][j - 1] if i - (1 << (j - 1)) >= 0 else 0
                if i > 0 and j < max_jumps:
                    dp[i][j] += dp[i - 1][j] if i - 1 >= 0 else 0

        return sum(dp[k]) % (10**9 + 7)