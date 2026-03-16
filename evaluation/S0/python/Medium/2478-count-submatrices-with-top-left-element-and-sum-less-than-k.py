# Source: https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer matrix grid and an integer k.
#
# Return the number of submatrices that contain the top-left element of the grid, and have a sum less than or equal to k.
#
# Example:
# Input: grid = [[7,6,3],[6,6,1]], k = 18
# Output: 4
# Explanation: There are only 4 submatrices, shown in the image above, that contain the top-left element of grid, and have a sum less than or equal to 18.
#
# Constraints:
# m == grid.length 
# 	n == grid[i].length
# 	1 <= n, m <= 1000 
# 	0 <= grid[i][j] <= 1000
# 	1 <= k <= 109
#

class Solution(object):
    def countSubmatrices(self, grid, k):
        """
        :type grid: List[List[int]]
        :type k: int
        :rtype: int
        """
        m = len(grid)
        n = len(grid[0])
        count = 0
        
        for i in range(m):
            for j in range(n):
                submatrix_sum = 0
                for x in range(i, m):
                    for y in range(j, n):
                        submatrix_sum += grid[x][y]
                        if submatrix_sum <= k:
                            count += 1
                        else:
                            break
                    if submatrix_sum > k:
                        break
        
        return count