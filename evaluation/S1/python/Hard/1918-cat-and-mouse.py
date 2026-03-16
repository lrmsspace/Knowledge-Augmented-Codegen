# Source: https://leetcode.com/problems/cat-and-mouse/   |   Difficulty: Hard
#
# Problem Description:
# A game on an undirected graph is played by two players, Mouse and Cat, who alternate turns.
#
# The graph is given as follows: graph[a] is a list of all nodes b such that ab is an edge of the graph.
#
# The mouse starts at node 1 and goes first, the cat starts at node 2 and goes second, and there is a hole at node 0.
#
# During each player's turn, they must travel along one edge of the graph that meets where they are.  For example, if the Mouse is at node 1, it must travel to any node in graph[1].
#
# Additionally, it is not allowed for the Cat to travel to the Hole (node 0).
#
# Then, the game can end in three ways:
#
#
# 	If ever the Cat occupies the same node as the Mouse, the Cat wins.
# 	If ever the Mouse reaches the Hole, the Mouse wins.
# 	If ever a position is repeated (i.e., the players are in the same position as a previous turn, and it is the same player's turn to move), the game is a draw.
#
#
# Given a graph, and assuming both players play optimally, return
#
#
# 	1 if the mouse wins the game,
# 	2 if the cat wins the game, or
# 	0 if the game is a draw.
#
# Example:
# Input: graph = [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
# Output: 0
#
# Constraints:
# 3 <= graph.length <= 50
# 	1 <= graph[i].length < graph.length
# 	0 <= graph[i][j] < graph.length
# 	graph[i][j] != i
# 	graph[i] is unique.
# 	The mouse and the cat can always move.
#
# Helpful references (internal KB):
# - Games on arbitrary graphs (graph, array, dfs, game-theory)
#   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
#   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
#   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
#   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
#   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
# - Placing Bishops on a Chessboard (array, counting, dp-2d)
#   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
#   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
#   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
#   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
#   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def catMouseGame(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: int
        """
        n = len(graph)
        DRAW, MOUSE_WIN, CAT_WIN = 0, 1, 2

        # state: (mouse_pos, cat_pos, turn) -> outcome
        state = {}
        degree = {}

        # Initialize degrees and terminal states
        for m in range(n):
            for c in range(n):
                degree[(m, c, 0)] = len(graph[m])  # mouse's turn
                degree[(m, c, 1)] = len(graph[c]) - (0 in graph[c])  # cat's turn

                if m == 0:
                    state[(m, c, 0)] = MOUSE_WIN
                    state[(m, c, 1)] = MOUSE_WIN
                elif m == c:
                    state[(m, c, 0)] = CAT_WIN
                    state[(m, c, 1)] = CAT_WIN

        queue = [key for key in state.keys()]

        while queue:
            m, c, t = queue.pop(0)
            outcome = state[(m, c, t)]
            prev_t = 1 - t

            # Get predecessors
            if t == 0:  # mouse's turn
                for prev_c in graph[c]:
                    if prev_c == 0: continue
                    if (m, prev_c, prev_t) not in state:
                        if outcome == MOUSE_WIN:
                            state[(m, prev_c, prev_t)] = MOUSE_WIN
                            queue.append((m, prev_c, prev_t))
                        else:
                            degree[(m, prev_c, prev_t)] -= 1
                            if degree[(m, prev_c, prev_t)] == 0:
                                state[(m, prev_c, prev_t)] = CAT_WIN
                                queue.append((m, prev_c, prev_t))
            else:  # cat's turn
                for prev_m in graph[m]:
                    if (prev_m, c, prev_t) not in state:
                        if outcome == CAT_WIN:
                            state[(prev_m, c, prev_t)] = CAT_WIN
                            queue.append((prev_m, c, prev_t))
                        else:
                            degree[(prev_m, c, prev_t)] -= 1
                            if degree[(prev_m, c, prev_t)] == 0:
                                state[(prev_m, c, prev_t)] = MOUSE_WIN
                                queue.append((prev_m, c, prev_t))
        return state.get((1, 2, 0), DRAW)   