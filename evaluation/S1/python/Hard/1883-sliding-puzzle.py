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
# Helpful references (internal KB):
# - Breadth-first search (graph, queue, array, bfs)
#   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
#   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
#   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
#   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
# - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
#   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
#   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
#   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
#   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
#   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
# - Suffix Automaton (graph, string, simulation)
#   • When to use: When needing to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings, finding occurrences, or checking for specific patterns. It provides a compact and powerful data structure for complex string problems.
#   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that recognizes all suffixes of a given string. It compactly represents all substrings of the string, with each state corresponding to an endpos-equivalence class, and can be constructed in linear time O(N).
#   • Invariants: Every state corresponds to a unique endpos-equivalence class of substrings.; For any state, all substrings ending at its endpos set are represented by that state or its ancestors via suffix links.
#   • Tips: Focus on the endpos definition for state equivalence.; Understand the incremental construction process.
#   • Pitfalls: The construction algorithm is non-trivial and prone to off-by-one errors.; Misinterpreting the role of suffix links vs. transition links.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def slidingPuzzle(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        # The target state of the board
        target = [[1, 2, 3], [4, 5, 0]]
        
        # Directions for moving the empty tile (0)
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        
        # Convert the board to a tuple for immutability and hashing
        start = tuple(tuple(row) for row in board)
        target = tuple(tuple(row) for row in target)
        
        # BFS initialization
        queue = [(start, start.index(0), 0)]  # (current state, index of zero, moves)
        visited = set()
        visited.add(start)
        
        while queue:
            current_state, zero_index, moves = queue.pop(0)
            
            if current_state == target:
                return moves
            
            # Get the position of zero
            zero_row, zero_col = zero_index // 3, zero_index % 3
            
            for dr, dc in directions:
                new_row, new_col = zero_row + dr, zero_col + dc
                
                if 0 <= new_row < 2 and 0 <= new_col < 3:
                    new_zero_index = new_row * 3 + new_col
                    
                    # Create a new state by swapping zero with the adjacent tile
                    new_state_list = [list(row) for row in current_state]
                    new_state_list[zero_row][zero_col], new_state_list[new_row][new_col] = new_state_list[new_row][new_col], new_state_list[zero_row][zero_col]
                    new_state = tuple(tuple(row) for row in new_state_list)
                    
                    if new_state not in visited:
                        visited.add(new_state)
                        queue.append((new_state, new_zero_index, moves + 1))
                        
        return -1       