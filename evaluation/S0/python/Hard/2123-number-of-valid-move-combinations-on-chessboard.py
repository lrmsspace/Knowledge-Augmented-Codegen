# Source: https://leetcode.com/problems/number-of-valid-move-combinations-on-chessboard/   |   Difficulty: Hard
#
# Problem Description:
# There is an 8 x 8 chessboard containing n pieces (rooks, queens, or bishops). You are given a string array pieces of length n, where pieces[i] describes the type (rook, queen, or bishop) of the ith piece. In addition, you are given a 2D integer array positions also of length n, where positions[i] = [ri, ci] indicates that the ith piece is currently at the 1-based coordinate (ri, ci) on the chessboard.
#
# When making a move for a piece, you choose a destination square that the piece will travel toward and stop on.
#
#
# 	A rook can only travel horizontally or vertically from (r, c) to the direction of (r+1, c), (r-1, c), (r, c+1), or (r, c-1).
# 	A queen can only travel horizontally, vertically, or diagonally from (r, c) to the direction of (r+1, c), (r-1, c), (r, c+1), (r, c-1), (r+1, c+1), (r+1, c-1), (r-1, c+1), (r-1, c-1).
# 	A bishop can only travel diagonally from (r, c) to the direction of (r+1, c+1), (r+1, c-1), (r-1, c+1), (r-1, c-1).
#
#
# You must make a move for every piece on the board simultaneously. A move combination consists of all the moves performed on all the given pieces. Every second, each piece will instantaneously travel one square towards their destination if they are not already at it. All pieces start traveling at the 0th second. A move combination is invalid if, at a given time, two or more pieces occupy the same square.
#
# Return the number of valid move combinations​​​​​.
#
#
# Example:
# Input: pieces = ["rook"], positions = [[1,1]]
# Output: 15
# Explanation: The image above shows the possible squares the piece can move to.
#
# Constraints:
# n == pieces.length 
# 	n == positions.length
# 	1 <= n <= 4
# 	pieces only contains the strings "rook", "queen", and "bishop".
# 	There will be at most one queen on the chessboard.
# 	1 <= ri, ci <= 8
# 	Each positions[i] is distinct.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countCombinations(self, pieces, positions):
        """
        :type pieces: List[str]
        :type positions: List[List[int]]
        :rtype: int
        """
            
        directions = {
            'rook': [(1, 0), (-1, 0), (0, 1), (0, -1)],
            'bishop': [(1, 1), (1, -1), (-1, 1), (-1, -1)],
            'queen': [(1, 0), (-1, 0), (0, 1), (0, -1), (1, 1), (1, -1), (-1, 1), (-1, -1)]
        }

        def get_moves(piece, pos):
            r, c = pos
            moves = []
            for dr, dc in directions[piece]:
                for step in range(1, 8):
                    nr, nc = r + dr * step, c + dc * step
                    if 1 <= nr <= 8 and 1 <= nc <= 8:
                        moves.append((nr, nc))
                    else:
                        break
            return moves

        all_moves = [get_moves(pieces[i], positions[i]) for i in range(len(pieces))]
        valid_combinations = 0

        from itertools import product

        for move_combination in product(*all_moves):
            time_positions = {}
            max_time = 0
            for i in range(len(pieces)):
                r1, c1 = positions[i]
                r2, c2 = move_combination[i]
                travel_time = max(abs(r2 - r1), abs(c2 - c1))
                max_time = max(max_time, travel_time)
                for t in range(travel_time + 1):
                    tr = r1 + (r2 - r1) * t // travel_time if travel_time != 0 else r1
                    tc = c1 + (c2 - c1) * t // travel_time if travel_time != 0 else c1
                    if t not in time_positions:
                        time_positions[t] = set()
                    if (tr, tc) in time_positions[t]:
                        break
                    time_positions[t].add((tr, tc))
                else:
                    continue
                break
            else:
                valid_combinations += 1

        return valid_combinations   