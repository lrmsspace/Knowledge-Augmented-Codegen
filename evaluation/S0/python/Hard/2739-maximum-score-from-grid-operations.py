# Source: https://leetcode.com/problems/maximum-score-from-grid-operations/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D matrix grid of size n x n. Initially, all cells of the grid are colored white. In one operation, you can select any cell of indices (i, j), and color black all the cells of the jth column starting from the top row down to the ith row.
#
# The grid score is the sum of all grid[i][j] such that cell (i, j) is white and it has a horizontally adjacent black cell.
#
# Return the maximum score that can be achieved after some number of operations.
#
# Example:
# Input: grid = [[0,0,0,0,0],[0,0,3,0,0],[0,1,0,0,0],[5,0,0,3,0],[0,0,0,0,2]]
#
# Output: 11
#
# Explanation:
#
# In the first operation, we color all cells in column 1 down to row 3, and in the second operation, we color all cells in column 4 down to the last row. The score of the resulting grid is grid[3][0] + grid[1][2] + grid[3][3] which is equal to 11.
#
# Constraints:
# 1 <= n == grid.length <= 100
# 	n == grid[i].length
# 	0 <= grid[i][j] <= 109
#

class Solution(object):
    def maximumScore(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        max_score = 0

        for mask in range(1 << n):
            black = [[False] * n for _ in range(n)]
            for j in range(n):
                for i in range(n):
                    if (mask >> j) & 1:
                        black[i][j] = True
                    else:
                        break

            score = 0
            for i in range(n):
                for j in range(1, n):
                    if not black[i][j] and black[i][j - 1]:
                        score += grid[i][j]

            max_score = max(max_score, score)

        return max_score