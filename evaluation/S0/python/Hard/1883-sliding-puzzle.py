# Source: https://leetcode.com/problems/sliding-puzzle/   |   Difficulty: Hard
#
# Problem Description:
# On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty square represented by 0. A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.
#
# The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].
#
# Given the puzzle board board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.
#
# Example:
# Input: board = [[1,2,3],[4,0,5]]
# Output: 1
# Explanation: Swap the 0 and the 5 in one move.
#
# Constraints:
# board.length == 2
# 	board[i].length == 3
# 	0 <= board[i][j] <= 5
# 	Each value board[i][j] is unique.
#

class Solution(object):
    def slidingPuzzle(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        start = ''.join(str(num) for row in board for num in row)
        target = '123450'
        neighbors = {
            0: [1, 3],
            1: [0, 2, 4],
            2: [1, 5],
            3: [0, 4],
            4: [1, 3, 5],
            5: [2, 4]
        }
        
        queue = [(start, start.index('0'), 0)]
        visited = set([start])
        
        while queue:
            state, zero_pos, moves = queue.pop(0)
            if state == target:
                return moves
            
            for neighbor in neighbors[zero_pos]:
                new_state = list(state)
                new_state[zero_pos], new_state[neighbor] = new_state[neighbor], new_state[zero_pos]
                new_state_str = ''.join(new_state)
                
                if new_state_str not in visited:
                    visited.add(new_state_str)
                    queue.append((new_state_str, neighbor, moves + 1))
        
        return -1