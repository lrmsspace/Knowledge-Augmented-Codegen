# Source: https://leetcode.com/problems/the-earliest-and-latest-rounds-where-players-compete/   |   Difficulty: Hard
#
# Problem Description:
# There is a tournament where n players are participating. The players are standing in a single row and are numbered from 1 to n based on their initial standing position (player 1 is the first player in the row, player 2 is the second player in the row, etc.).
#
# The tournament consists of multiple rounds (starting from round number 1). In each round, the ith player from the front of the row competes against the ith player from the end of the row, and the winner advances to the next round. When the number of players is odd for the current round, the player in the middle automatically advances to the next round.
#
#
# 	For example, if the row consists of players 1, 2, 4, 6, 7
#
# 	
# 		Player 1 competes against player 7.
# 		Player 2 competes against player 6.
# 		Player 4 automatically advances to the next round.
# 	
# 	
#
#
# After each round is over, the winners are lined back up in the row based on the original ordering assigned to them initially (ascending order).
#
# The players numbered firstPlayer and secondPlayer are the best in the tournament. They can win against any other player before they compete against each other. If any two other players compete against each other, either of them might win, and thus you may choose the outcome of this round.
#
# Given the integers n, firstPlayer, and secondPlayer, return an integer array containing two values, the earliest possible round number and the latest possible round number in which these two players will compete against each other, respectively.
#
# Example:
# Input: n = 11, firstPlayer = 2, secondPlayer = 4
# Output: [3,4]
# Explanation:
# One possible scenario which leads to the earliest round number:
# First round: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
# Second round: 2, 3, 4, 5, 6, 11
# Third round: 2, 3, 4
# One possible scenario which leads to the latest round number:
# First round: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
# Second round: 1, 2, 3, 4, 5, 6
# Third round: 1, 2, 4
# Fourth round: 2, 4
#
# Constraints:
# 2 <= n <= 28
# 	1 <= firstPlayer < secondPlayer <= n
#
# Helpful references (internal KB):
# - Josephus Problem (number, recursion, counting)
#   • When to use: Use when simulating a circular elimination process with a fixed step size, especially when seeking the survivor's position. It's particularly efficient for specific step sizes like two.
#   • Idea: The Josephus Problem determines the last remaining position in a circular arrangement after elements are eliminated at fixed intervals. The recursive solution for a step size of two has a logarithmic time complexity, O(log N), due to its divide-and-conquer nature.
#   • Invariants: The number of participants N is always positive in each recursive subproblem.; The returned position is always within the valid range [0, current N-1] (or [1, current N]).
#   • Tips: Base cases are crucial for recursive solutions, typically for N=1.; Observe patterns for specific step sizes, especially k=2, which has a simpler formula.
#   • Pitfalls: Off-by-one errors when converting between 0-indexed and 1-indexed results.; Incorrectly applying the position 'shift' after elements are eliminated in subproblems.
# - Games on arbitrary graphs (graph, array, dfs, game-theory)
#   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
#   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
#   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
#   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
#   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
# - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
#   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
#   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
#   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
#   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def earliestAndLatest(self, n, firstPlayer, secondPlayer):
        """
        :type n: int
        :type firstPlayer: int
        :type secondPlayer: int
        :rtype: List[int]
        """
        def helper(players, fp, sp):
            if len(players) == 2:
                return 1
            fp_idx = players.index(fp)
            sp_idx = players.index(sp)
            if fp_idx + sp_idx == len(players) - 1:
                return 1
            next_players = []
            for i in range((len(players) + 1) // 2):
                if i != fp_idx and i != sp_idx and len(players) - 1 - i != fp_idx and len(players) - 1 - i != sp_idx:
                    next_players.append(players[i])
            next_players.append(fp)
            next_players.append(sp)
            next_players.sort()
            return helper(next_players, fp, sp) + 1

        earliest = helper(list(range(1, n + 1)), firstPlayer, secondPlayer)

        def helper_latest(players, fp, sp):
            if len(players) == 2:
                return 1
            fp_idx = players.index(fp)
            sp_idx = players.index(sp)
            if fp_idx + sp_idx == len(players) - 1:
                return 1
            next_players = []
            for i in range((len(players) + 1) // 2):
                if (i == fp_idx or i == sp_idx or len(players) - 1 - i == fp_idx or len(players) - 1 - i == sp_idx):
                    next_players.append(players[i])
                else:
                    next_players.append(players[i])
                    next_players.append(players[len(players) - 1 - i])
            next_players.sort()
            return helper_latest(next_players, fp, sp) + 1

        latest = helper_latest(list(range(1, n + 1)), firstPlayer, secondPlayer)

        return [earliest, latest]