# Source: https://leetcode.com/problems/score-after-flipping-matrix/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n binary matrix grid.
#
# A move consists of choosing any row or column and toggling each value in that row or column (i.e., changing all 0's to 1's, and all 1's to 0's).
#
# Every row of the matrix is interpreted as a binary number, and the score of the matrix is the sum of these numbers.
#
# Return the highest possible score after making any number of moves (including zero moves).
#
# Example:
# Input: grid = [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
# Output: 39
# Explanation: 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 20
# 	grid[i][j] is either 0 or 1.
#

class Solution(object):
    def matrixScore(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m = len(grid)
        n = len(grid[0])
        
        # Step 1: Ensure the first column has all 1s
        for i in range(m):
            if grid[i][0] == 0:
                for j in range(n):
                    grid[i][j] ^= 1  # Flip the entire row
        
        # Step 2: Maximize the number of 1s in each column from the second column onwards
        for j in range(1, n):
            count_ones = sum(grid[i][j] for i in range(m))
            if count_ones < m / 2:
                for i in range(m):
                    grid[i][j] ^= 1  # Flip the entire column
        
        # Step 3: Calculate the total score
        total_score = 0
        for i in range(m):
            row_value = 0
            for j in range(n):
                row_value = (row_value << 1) | grid[i][j]
            total_score += row_value
        
        return total_score