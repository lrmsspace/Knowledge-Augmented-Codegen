# Source: https://leetcode.com/problems/cat-and-mouse-ii/   |   Difficulty: Hard
#
# Problem Description:
# A game is played by a cat and a mouse named Cat and Mouse.
#
# The environment is represented by a grid of size rows x cols, where each element is a wall, floor, player (Cat, Mouse), or food.
#
#
# 	Players are represented by the characters 'C'(Cat),'M'(Mouse).
# 	Floors are represented by the character '.' and can be walked on.
# 	Walls are represented by the character '#' and cannot be walked on.
# 	Food is represented by the character 'F' and can be walked on.
# 	There is only one of each character 'C', 'M', and 'F' in grid.
#
#
# Mouse and Cat play according to the following rules:
#
#
# 	Mouse moves first, then they take turns to move.
# 	During each turn, Cat and Mouse can jump in one of the four directions (left, right, up, down). They cannot jump over the wall nor outside of the grid.
# 	catJump, mouseJump are the maximum lengths Cat and Mouse can jump at a time, respectively. Cat and Mouse can jump less than the maximum length.
# 	Staying in the same position is allowed.
# 	Mouse can jump over Cat.
#
#
# The game can end in 4 ways:
#
#
# 	If Cat occupies the same position as Mouse, Cat wins.
# 	If Cat reaches the food first, Cat wins.
# 	If Mouse reaches the food first, Mouse wins.
# 	If Mouse cannot get to the food within 1000 turns, Cat wins.
#
#
# Given a rows x cols matrix grid and two integers catJump and mouseJump, return true if Mouse can win the game if both Cat and Mouse play optimally, otherwise return false.
#
# Example:
# Input: grid = ["####F","#C...","M...."], catJump = 1, mouseJump = 2
# Output: true
# Explanation: Cat cannot catch Mouse on its turn nor can it get the food before Mouse.
#
# Constraints:
# rows == grid.length
# 	cols = grid[i].length
# 	1 <= rows, cols <= 8
# 	grid[i][j] consist only of characters 'C', 'M', 'F', '.', and '#'.
# 	There is only one of each character 'C', 'M', and 'F' in grid.
# 	1 <= catJump, mouseJump <= 8
#
# Helpful references (internal KB):
# - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
#   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
#   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
#   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
#   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
#   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
# - Games on arbitrary graphs (graph, array, dfs, game-theory)
#   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
#   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
#   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
#   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
#   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def canMouseWin(self, grid, catJump, mouseJump):
        """
        :type grid: List[str]
        :type catJump: int
        :type mouseJump: int
        :rtype: bool
        """
        from collections import deque

        rows, cols = len(grid), len(grid[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

        # Locate positions of Mouse, Cat, and Food
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 'M':
                    mouse_start = (r, c)
                elif grid[r][c] == 'C':
                    cat_start = (r, c)
                elif grid[r][c] == 'F':
                    food_pos = (r, c)

        # State: (mouse_x, mouse_y, cat_x, cat_y, turn)
        # turn: 0 for Mouse's turn, 1 for Cat's turn
        max_turns = 1000
        memo = {}

        def is_valid(x, y):
            return 0 <= x < rows and 0 <= y < cols and grid[x][y] != '#'

        def dfs(mouse_pos, cat_pos, turn, depth):
            if depth > max_turns:
                return False  # Cat wins if Mouse can't reach food in time
            if mouse_pos == cat_pos or cat_pos == food_pos:
                return False  # Cat wins
            if mouse_pos == food_pos:
                return True  # Mouse wins

            state = (mouse_pos, cat_pos, turn)
            if state in memo:
                return memo[state]

            if turn == 0:  # Mouse's turn
                for dx, dy in directions:
                    for jump in range(mouseJump + 1):
                        new_mouse_x = mouse_pos[0] + dx * jump
                        new_mouse_y = mouse_pos[1] + dy * jump
                        if not is_valid(new_mouse_x, new_mouse_y):
                            break
                        if dfs((new_mouse_x, new_mouse_y), cat_pos, 1, depth + 1):
                            memo[state] = True
                            return True
                memo[state] = False
                return False
            else:  # Cat's turn
                for dx, dy in directions:
                    for jump in range(catJump + 1):
                        new_cat_x = cat_pos[0] + dx * jump
                        new_cat_y = cat_pos[1] + dy * jump
                        if not is_valid(new_cat_x, new_cat_y):
                            break
                        if not dfs(mouse_pos, (new_cat_x, new_cat_y), 0, depth + 1):
                            memo[state] = False
                            return False
                memo[state] = True
                return True
        return dfs(mouse_start, cat_start, 0, 0)    