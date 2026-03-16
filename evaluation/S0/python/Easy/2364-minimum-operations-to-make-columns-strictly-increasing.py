# Source: https://leetcode.com/problems/minimum-operations-to-make-columns-strictly-increasing/   |   Difficulty: Easy
#
# Problem Description:
# You are given a m x n matrix grid consisting of non-negative integers.
#
# In one operation, you can increment the value of any grid[i][j] by 1.
#
# Return the minimum number of operations needed to make all columns of grid strictly increasing.
#
# Example:
# Input: grid = [[3,2],[1,3],[3,4],[0,1]]
#
# Output: 15
#
# Explanation:
#
#
# 	To make the 0th column strictly increasing, we can apply 3 operations on grid[1][0], 2 operations on grid[2][0], and 6 operations on grid[3][0].
# 	To make the 1st column strictly increasing, we can apply 4 operations on grid[3][1].
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 50
# 	0 <= grid[i][j] < 2500
#

class Solution(object):
    def minimumOperations(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        operations = 0
        
        for col in range(n):
            for row in range(1, m):
                if grid[row][col] <= grid[row - 1][col]:
                    needed = grid[row - 1][col] - grid[row][col] + 1
                    operations += needed
                    grid[row][col] += needed
                    
        return operations