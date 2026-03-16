# Source: https://leetcode.com/problems/count-servers-that-communicate/   |   Difficulty: Medium
#
# Problem Description:
# You are given a map of a server center, represented as a m * n integer matrix grid, where 1 means that on that cell there is a server and 0 means that it is no server. Two servers are said to communicate if they are on the same row or on the same column.
#
# Return the number of servers that communicate with any other server.
#
# Example:
# Input: grid = [[1,0],[0,1]]
# Output: 0
# Explanation: No servers can communicate with others.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m <= 250
# 	1 <= n <= 250
# 	grid[i][j] == 0 or 1
#

class Solution(object):
    def countServers(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        row_count = [0] * len(grid)
        col_count = [0] * len(grid[0])
        
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 1:
                    row_count[i] += 1
                    col_count[j] += 1
        
        result = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 1 and (row_count[i] > 1 or col_count[j] > 1):
                    result += 1
        
        return result