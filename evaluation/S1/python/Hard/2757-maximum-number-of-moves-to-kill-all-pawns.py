# Source: https://leetcode.com/problems/maximum-number-of-moves-to-kill-all-pawns/   |   Difficulty: Hard
#
# Problem Description:
# There is a 50 x 50 chessboard with one knight and some pawns on it. You are given two integers kx and ky where (kx, ky) denotes the position of the knight, and a 2D array positions where positions[i] = [xi, yi] denotes the position of the pawns on the chessboard.
#
# Alice and Bob play a turn-based game, where Alice goes first. In each player's turn:
#
#
# 	The player selects a pawn that still exists on the board and captures it with the knight in the fewest possible moves. Note that the player can select any pawn, it might not be one that can be captured in the least number of moves.
# 	In the process of capturing the selected pawn, the knight may pass other pawns without capturing them. Only the selected pawn can be captured in this turn.
#
#
# Alice is trying to maximize the sum of the number of moves made by both players until there are no more pawns on the board, whereas Bob tries to minimize them.
#
# Return the maximum total number of moves made during the game that Alice can achieve, assuming both players play optimally.
#
# Note that in one move, a chess knight has eight possible positions it can move to, as illustrated below. Each move is two cells in a cardinal direction, then one cell in an orthogonal direction.
#
# Example:
# Input: kx = 1, ky = 1, positions = [[0,0]]
#
# Output: 4
#
# Explanation:
#
#
#
# The knight takes 4 moves to reach the pawn at (0, 0).
#
# Constraints:
# 0 <= kx, ky <= 49
# 	1 <= positions.length <= 15
# 	positions[i].length == 2
# 	0 <= positions[i][0], positions[i][1] <= 49
# 	All positions[i] are unique.
# 	The input is generated such that positions[i] != [kx, ky] for all 0 <= i < positions.length.
#
# Helpful references (internal KB):
# - Breadth-first search (graph, queue, array, bfs)
#   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
#   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
#   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
#   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
# - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
#   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
#   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
#   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
#   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
#   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
# - Submask Enumeration
#  (number, bitset, enumeration, bitmask-dp)
#   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
#   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
#   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
#   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
#   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxMoves(self, kx, ky, positions):
        """
        :type kx: int
        :type ky: int
        :type positions: List[List[int]]
        :rtype: int
        """
        # Step 1: Calculate the shortest distance from the knight's starting position to each pawn using BFS.
        def bfs(start, target):
            directions = [(2, 1), (2, -1), (-2, 1), (-2, -1), (1, 2), (1, -2), (-1, 2), (-1, -2)]
            queue = collections.deque([(start[0], start[1], 0)])  # (x, y, distance)
            visited = set()
            visited.add((start[0], start[1]))

            while queue:
                x, y, dist = queue.popleft()
                if (x, y) == target:
                    return dist
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < 50 and 0 <= ny < 50 and (nx, ny) not in visited:
                        visited.add((nx, ny))
                        queue.append((nx, ny, dist + 1))
            return float('inf')  # If target is unreachable

        # Step 2: Create a list of distances from the knight to each pawn.
        distances = []
        for pos in positions:
            dist = bfs((kx, ky), (pos[0], pos[1]))
            distances.append(dist)

        # Step 3: Use a bitmask to represent the state of captured pawns and apply minimax with memoization.
        n = len(positions)
        memo = {}

        def minimax(mask):
            if mask == (1 << n) - 1:  # All pawns captured
                return 0
            if mask in memo:
                return memo[mask]

            best_score = float('-inf')
            for i in range(n):
                if not (mask & (1 << i)):  # If pawn i is not captured
                    score = distances[i] + minimax(mask | (1 << i))
                    best_score = max(best_score, score)

            memo[mask] = best_score
            return best_score

        return minimax(0)