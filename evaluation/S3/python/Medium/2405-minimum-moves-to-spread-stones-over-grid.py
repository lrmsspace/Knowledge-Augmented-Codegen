# Source: https://leetcode.com/problems/minimum-moves-to-spread-stones-over-grid/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed 2D integer matrix grid of size 3 * 3, representing the number of stones in each cell. The grid contains exactly 9 stones, and there can be multiple stones in a single cell.
#
# In one move, you can move a single stone from its current cell to any other cell if the two cells share a side.
#
# Return the minimum number of moves required to place one stone in each cell.
#
# Example:
# Input: grid = [[1,1,0],[1,1,1],[1,2,1]]
# Output: 3
# Explanation: One possible sequence of moves to place one stone in each cell is: 
# 1- Move one stone from cell (2,1) to cell (2,2).
# 2- Move one stone from cell (2,2) to cell (1,2).
# 3- Move one stone from cell (1,2) to cell (0,2).
# In total, it takes 3 moves to place one stone in each cell of the grid.
# It can be shown that 3 is the minimum number of moves required to place one stone in each cell.
#
# Constraints:
# grid.length == grid[i].length == 3
# 	0 <= grid[i][j] <= 9
# 	Sum of grid is equal to 9.
#
# Helpful references (internal KB):
# - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
#   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
#   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
#   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
#   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
#   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
# - Finding the equation of a line for a segment (geometry, number, enumeration)
#   • When to use: Use when the problem asks to count or list all possible combinations, permutations, or arrangements of elements. It's suitable when a brute-force check of all possibilities is feasible.
#   • Idea: Enumeration systematically generates and examines all possible solutions to a problem. This approach guarantees finding the correct answer if one exists, typically with exponential time complexity O(k^N) or O(N!).
#   • Invariants: At each step, the current partial solution is valid according to problem constraints.; All previously explored partial solutions have been processed or discarded.
#   • Tips: Clearly define the search space and the properties of valid solutions.; Use recursion or iterative loops to explore all branches of the solution space.
#   • Pitfalls: Overlooking edge cases or constraints that limit the search space.; Generating duplicate solutions if not handled carefully.
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
    def minimumMoves(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        # Step 1: Collect all stone positions
        stones = []
        for i in range(3):
            for j in range(3):
                for _ in range(grid[i][j]):
                    stones.append((i, j))

        # Step 2: Calculate the target positions (one stone per cell)
        targets = [(i, j) for i in range(3) for j in range(3)]

        # Step 3: Calculate the total moves using Manhattan distance
        total_moves = 0
        for stone, target in zip(stones, targets):
            total_moves += abs(stone[0] - target[0]) + abs(stone[1] - target[1])

        return total_moves