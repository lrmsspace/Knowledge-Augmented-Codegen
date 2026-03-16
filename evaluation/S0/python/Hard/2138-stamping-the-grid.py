# Source: https://leetcode.com/problems/stamping-the-grid/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n binary matrix grid where each cell is either 0 (empty) or 1 (occupied).
#
# You are then given stamps of size stampHeight x stampWidth. We want to fit the stamps such that they follow the given restrictions and requirements:
#
#
# 	Cover all the empty cells.
# 	Do not cover any of the occupied cells.
# 	We can put as many stamps as we want.
# 	Stamps can overlap with each other.
# 	Stamps are not allowed to be rotated.
# 	Stamps must stay completely inside the grid.
#
#
# Return true if it is possible to fit the stamps while following the given restrictions and requirements. Otherwise, return false.
#
# Example:
# Input: grid = [[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0]], stampHeight = 4, stampWidth = 3
# Output: true
# Explanation: We have two overlapping stamps (labeled 1 and 2 in the image) that are able to cover all the empty cells.
#
# Constraints:
# m == grid.length
# 	n == grid[r].length
# 	1 <= m, n <= 105
# 	1 <= m * n <= 2 * 105
# 	grid[r][c] is either 0 or 1.
# 	1 <= stampHeight, stampWidth <= 105
#

class Solution(object):
    def possibleToStamp(self, grid, stampHeight, stampWidth):
        """
        :type grid: List[List[int]]
        :type stampHeight: int
        :type stampWidth: int
        :rtype: bool
        """
        m, n = len(grid), len(grid[0])
        
        # Precompute the prefix sum of occupied cells
        prefix_sum = [[0] * (n + 1) for _ in range(m + 1)]
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                prefix_sum[i][j] = grid[i - 1][j - 1] + prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1]
        
        def can_place_stamp(x1, y1, x2, y2):
            total = prefix_sum[x2][y2] - prefix_sum[x1][y2] - prefix_sum[x2][y1] + prefix_sum[x1][y1]
            return total == 0
        
        stampable = [[0] * n for _ in range(m)]
        
        for i in range(m - stampHeight + 1):
            for j in range(n - stampWidth + 1):
                if can_place_stamp(i, j, i + stampHeight, j + stampWidth):
                    stampable[i][j] = 1
        
        # Create a coverage matrix
        coverage = [[0] * (n + 1) for _ in range(m + 1)]
        
        for i in range(m):
            for j in range(n):
                if stampable[i][j]:
                    coverage[i][j] += 1
                    coverage[i + stampHeight][j] -= 1
                    coverage[i][j + stampWidth] -= 1
                    coverage[i + stampHeight][j + stampWidth] += 1
        
        # Compute the final coverage using prefix sums
        for i in range(m):
            for j in range(n):
                if i > 0:
                    coverage[i][j] += coverage[i - 1][j]
                if j > 0:
                    coverage[i][j] += coverage[i][j - 1]
                if i > 0 and j > 0:
                    coverage[i][j] -= coverage[i - 1][j - 1]
        
        # Check if all empty cells are covered
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 0 and coverage[i][j] <= 0:
                    return False    
        return True 