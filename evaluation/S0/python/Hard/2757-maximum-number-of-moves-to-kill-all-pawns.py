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

class Solution(object):
    def maxMoves(self, kx, ky, positions):
        """
        :type kx: int
        :type ky: int
        :type positions: List[List[int]]
        :rtype: int
        """
        from collections import deque

        def bfs(start, end):
            directions = [(2, 1), (1, 2), (-1, 2), (-2, 1), (-2, -1), (-1, -2), (1, -2), (2, -1)]
            queue = deque([start])
            visited = set()
            visited.add(start)
            moves = 0

            while queue:
                for _ in range(len(queue)):
                    x, y = queue.popleft()
                    if (x, y) == end:
                        return moves
                    for dx, dy in directions:
                        nx, ny = x + dx, y + dy
                        if 0 <= nx < 50 and 0 <= ny < 50 and (nx, ny) not in visited:
                            visited.add((nx, ny))
                            queue.append((nx, ny))
                moves += 1
            return float('inf')

        n = len(positions)
        dist = [[0] * n for _ in range(n)]
        start_dist = [0] * n

        for i in range(n):
            start_dist[i] = bfs((kx, ky), (positions[i][0], positions[i][1]))
            for j in range(n):
                if i != j:
                    dist[i][j] = bfs((positions[i][0], positions[i][1]), (positions[j][0], positions[j][1]))

        from functools import lru_cache

        @lru_cache(None)
        def dp(mask, turn):
            if mask == (1 << n) - 1:
                return 0
            if turn == 0:  # Alice's turn
                max_moves = float('-inf')
                for i in range(n):
                    if not (mask & (1 << i)):
                        max_moves = max(max_moves, start_dist[i] + dp(mask | (1 << i), 1))
                return max_moves
            else:  # Bob's turn
                min_moves = float('inf')
                for i in range(n):
                    if not (mask & (1 << i)):
                        min_moves = min(min_moves, start_dist[i] + dp(mask | (1 << i), 0))
                return min_moves

        return dp(0, 0)