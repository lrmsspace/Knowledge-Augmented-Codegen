# Source: https://leetcode.com/problems/construct-product-matrix/   |   Difficulty: Medium
#
# Problem Description:
# Given a 0-indexed 2D integer matrix grid of size n * m, we define a 0-indexed 2D matrix p of size n * m as the product matrix of grid if the following condition is met:
#
#
# 	Each element p[i][j] is calculated as the product of all elements in grid except for the element grid[i][j]. This product is then taken modulo 12345.
#
#
# Return the product matrix of grid.
#
# Example:
# Input: grid = [[1,2],[3,4]]
# Output: [[24,12],[8,6]]
# Explanation: p[0][0] = grid[0][1] * grid[1][0] * grid[1][1] = 2 * 3 * 4 = 24
# p[0][1] = grid[0][0] * grid[1][0] * grid[1][1] = 1 * 3 * 4 = 12
# p[1][0] = grid[0][0] * grid[0][1] * grid[1][1] = 1 * 2 * 4 = 8
# p[1][1] = grid[0][0] * grid[0][1] * grid[1][0] = 1 * 2 * 3 = 6
# So the answer is [[24,12],[8,6]].
#
# Constraints:
# 1 <= n == grid.length <= 105
# 	1 <= m == grid[i].length <= 105
# 	2 <= n * m <= 105
# 	1 <= grid[i][j] <= 109
#

class Solution(object):
    def constructProductMatrix(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: List[List[int]]
        """
        MOD = 12345
        n = len(grid)
        m = len(grid[0]) if n > 0 else 0
        
        total_product = 1
        zero_count = 0
        
        for i in range(n):
            for j in range(m):
                if grid[i][j] == 0:
                    zero_count += 1
                else:
                    total_product = (total_product * grid[i][j]) % MOD
        
        product_matrix = [[0] * m for _ in range(n)]
        
        for i in range(n):
            for j in range(m):
                if zero_count > 1:
                    product_matrix[i][j] = 0
                elif zero_count == 1:
                    if grid[i][j] == 0:
                        product_matrix[i][j] = total_product
                    else:
                        product_matrix[i][j] = 0
                else:
                    inv_element = pow(grid[i][j], MOD - 2, MOD)
                    product_matrix[i][j] = (total_product * inv_element) % MOD
        
        return product_matrix