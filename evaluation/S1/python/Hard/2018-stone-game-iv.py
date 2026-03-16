# Source: https://leetcode.com/problems/stone-game-iv/   |   Difficulty: Hard
#
# Problem Description:
# Alice and Bob take turns playing a game, with Alice starting first.
#
# Initially, there are n stones in a pile. On each player's turn, that player makes a move consisting of removing any non-zero square number of stones in the pile.
#
# Also, if a player cannot make a move, he/she loses the game.
#
# Given a positive integer n, return true if and only if Alice wins the game otherwise return false, assuming both players play optimally.
#
# Example:
# Input: n = 1
# Output: true
# Explanation: Alice can remove 1 stone winning the game because Bob doesn't have any moves.
#
# Constraints:
# 1 <= n <= 105
#
# Helpful references (internal KB):
# - Games on arbitrary graphs (graph, array, dfs, game-theory)
#   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
#   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
#   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
#   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
#   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
# - Knapsack Problem (array, knapsack, dp-1d, enumeration)
#   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
#   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
#   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
#   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
#   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
# - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
#   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
#   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
#   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
#   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
#   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def winnerSquareGame(self, n):
        """
        :type n: int
        :rtype: bool
        """
        # dp[i] indicates whether the current player can win with i stones remaining
        dp = [False] * (n + 1)

        for i in range(1, n + 1):
            j = 1
            while j * j <= i:
                if not dp[i - j * j]:  # If the opponent loses with i - j*j stones, current player wins
                    dp[i] = True
                    break
                j += 1

        return dp[n]