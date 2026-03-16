# Source: https://leetcode.com/problems/difference-of-number-of-distinct-values-on-diagonals/   |   Difficulty: Medium
#
# Problem Description:
# Given a 2D grid of size m x n, you should find the matrix answer of size m x n.
#
# The cell answer[r][c] is calculated by looking at the diagonal values of the cell grid[r][c]:
#
#
# 	Let leftAbove[r][c] be the number of distinct values on the diagonal to the left and above the cell grid[r][c] not including the cell grid[r][c] itself.
# 	Let rightBelow[r][c] be the number of distinct values on the diagonal to the right and below the cell grid[r][c], not including the cell grid[r][c] itself.
# 	Then answer[r][c] = |leftAbove[r][c] - rightBelow[r][c]|.
#
#
# A matrix diagonal is a diagonal line of cells starting from some cell in either the topmost row or leftmost column and going in the bottom-right direction until the end of the matrix is reached.
#
#
# 	For example, in the below diagram the diagonal is highlighted using the cell with indices (2, 3) colored gray:
#
# 	
# 		Red-colored cells are left and above the cell.
# 		Blue-colored cells are right and below the cell.
# 	
# 	
#
#
#
#
# Return the matrix answer.
#
# Example:
# Input: grid = [[1,2,3],[3,1,5],[3,2,1]]
#
# Output: Output: [[1,1,0],[1,0,1],[0,1,1]]
#
# Explanation:
#
# To calculate the answer cells:
#
#
# 	
# 		
# 			answer
# 			left-above elements
# 			leftAbove
# 			right-below elements
# 			rightBelow
# 			|leftAbove - rightBelow|
# 		
# 	
# 	
# 		
# 			[0][0]
# 			[]
# 			0
# 			[grid[1][1], grid[2][2]]
# 			|{1, 1}| = 1
# 			1
# 		
# 		
# 			[0][1]
# 			[]
# 			0
# 			[grid[1][2]]
# 			|{5}| = 1
# 			1
# 		
# 		
# 			[0][2]
# 			[]
# 			0
# 			[]
# 			0
# 			0
# 		
# 		
# 			[1][0]
# 			[]
# 			0
# 			[grid[2][1]]
# 			|{2}| = 1
# 			1
# 		
# 		
# 			[1][1]
# 			[grid[0][0]]
# 			|{1}| = 1
# 			[grid[2][2]]
# 			|{1}| = 1
# 			0
# 		
# 		
# 			[1][2]
# 			[grid[0][1]]
# 			|{2}| = 1
# 			[]
# 			0
# 			1
# 		
# 		
# 			[2][0]
# 			[]
# 			0
# 			[]
# 			0
# 			0
# 		
# 		
# 			[2][1]
# 			[grid[1][0]]
# 			|{3}| = 1
# 			[]
# 			0
# 			1
# 		
# 		
# 			[2][2]
# 			[grid[0][0], grid[1][1]]
# 			|{1, 1}| = 1
# 			[]
# 			0
# 			1
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n, grid[i][j] <= 50
#

class Solution(object):
    def differenceOfDistinctValues(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: List[List[int]]
        """
        m, n = len(grid), len(grid[0])
        left_above = [[0] * n for _ in range(m)]
        right_below = [[0] * n for _ in range(m)]
        
        # Calculate leftAbove
        for r in range(m):
            for c in range(n):
                if r > 0 and c > 0:
                    left_above[r][c] = left_above[r-1][c-1] | {grid[r-1][c-1]}
                else:
                    left_above[r][c] = set()
        
        # Calculate rightBelow
        for r in range(m-1, -1, -1):
            for c in range(n-1, -1, -1):
                if r < m-1 and c < n-1:
                    right_below[r][c] = right_below[r+1][c+1] | {grid[r+1][c+1]}
                else:
                    right_below[r][c] = set()
        
        # Calculate the answer
        answer = [[0] * n for _ in range(m)]
        for r in range(m):
            for c in range(n):
                answer[r][c] = abs(len(left_above[r][c]) - len(right_below[r][c]))
        
        return answer