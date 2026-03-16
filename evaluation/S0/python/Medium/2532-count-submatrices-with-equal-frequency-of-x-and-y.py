# Source: https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/   |   Difficulty: Medium
#
# Problem Description:
# Given a 2D character matrix grid, where grid[i][j] is either 'X', 'Y', or '.', return the number of submatrices that contain:
#
#
# 	grid[0][0]
# 	an equal frequency of 'X' and 'Y'.
# 	at least one 'X'.
#
# Example:
# Input: grid = [["X","Y","."],["Y",".","."]]
#
# Output: 3
#
# Explanation:
#
# Constraints:
# 1 <= grid.length, grid[i].length <= 1000
# 	grid[i][j] is either 'X', 'Y', or '.'.
#

class Solution(object):
    def numberOfSubmatrices(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        result = 0

        for top in range(m):
            count_map = {}
            for left in range(n):
                count_x = 0
                count_y = 0
                for bottom in range(top, m):
                    if grid[bottom][left] == 'X':
                        count_x += 1
                    elif grid[bottom][left] == 'Y':
                        count_y += 1

                    key = (count_x - count_y)
                    if key == 0 and count_x > 0:
                        result += 1

                    if key in count_map:
                        result += count_map[key]
                    
                    count_map[key] = count_map.get(key, 0) + 1

        return result