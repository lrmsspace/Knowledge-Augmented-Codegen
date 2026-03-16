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

class Solution(object):
    def minimumMoves(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        moves = 0
        stones = []
        empties = []
        
        for r in range(3):
            for c in range(3):
                if grid[r][c] > 1:
                    for _ in range(grid[r][c] - 1):
                        stones.append((r, c))
                elif grid[r][c] == 0:
                    empties.append((r, c))
        
        for stone, empty in zip(stones, empties):
            moves += abs(stone[0] - empty[0]) + abs(stone[1] - empty[1])
        
        return moves