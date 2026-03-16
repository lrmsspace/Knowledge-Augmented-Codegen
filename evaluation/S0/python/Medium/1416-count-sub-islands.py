# Source: https://leetcode.com/problems/count-sub-islands/   |   Difficulty: Medium
#
# Problem Description:
# You are given two m x n binary matrices grid1 and grid2 containing only 0's (representing water) and 1's (representing land). An island is a group of 1's connected 4-directionally (horizontal or vertical). Any cells outside of the grid are considered water cells.
#
# An island in grid2 is considered a sub-island if there is an island in grid1 that contains all the cells that make up this island in grid2.
#
# Return the number of islands in grid2 that are considered sub-islands.
#
# Example:
# Input: grid1 = [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]], grid2 = [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]
# Output: 3
# Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
# The 1s colored red in grid2 are those considered to be part of a sub-island. There are three sub-islands.
#
# Constraints:
# m == grid1.length == grid2.length
# 	n == grid1[i].length == grid2[i].length
# 	1 <= m, n <= 500
# 	grid1[i][j] and grid2[i][j] are either 0 or 1.
#

class Solution(object):
    def countSubIslands(self, grid1, grid2):
        """
        :type grid1: List[List[int]]
        :type grid2: List[List[int]]
        :rtype: int
        """
        def dfs(i, j):
            if i < 0 or i >= len(grid2) or j < 0 or j >= len(grid2[0]) or grid2[i][j] == 0:
                return True
            grid2[i][j] = 0
            res = True
            if grid1[i][j] == 0:
                res = False
            res = dfs(i + 1, j) and res
            res = dfs(i - 1, j) and res
            res = dfs(i, j + 1) and res
            res = dfs(i, j - 1) and res
            return res

        count = 0
        for i in range(len(grid2)):
            for j in range(len(grid2[0])):
                if grid2[i][j] == 1:
                    if dfs(i, j):
                        count += 1
        return count