# Source: https://leetcode.com/problems/right-triangles/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D boolean matrix grid.
#
# A collection of 3 elements of grid is a right triangle if one of its elements is in the same row with another element and in the same column with the third element. The 3 elements may not be next to each other.
#
# Return an integer that is the number of right triangles that can be made with 3 elements of grid such that all of them have a value of 1.
#
# Example:
# 0
# 			1
# 			0
# 		
# 		
# 			0
# 			1
# 			1
# 		
# 		
# 			0
# 			1
# 			0
# 		
# 	
#
#
#
# 	
# 		
# 			0
# 			1
# 			0
# 		
# 		
# 			0
# 			1
# 			1
# 		
# 		
# 			0
# 			1
# 			0
# 		
# 	
#
#
#
# 	
# 		
# 			0
# 			1
# 			0
# 		
# 		
# 			0
# 			1
# 			1
# 		
# 		
# 			0
# 			1
# 			0
# 		
# 	
#
#
#
#
# Input: grid = [[0,1,0],[0,1,1],[0,1,0]]
#
# Output: 2
#
# Explanation:
#
# There are two right triangles with elements of the value 1. Notice that the blue ones do not form a right triangle because the 3 elements are in the same column.
#
# Constraints:
# 1 <= grid.length <= 1000
# 	1 <= grid[i].length <= 1000
# 	0 <= grid[i][j] <= 1
#

class Solution(object):
    def numberOfRightTriangles(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        row_counts = [0] * len(grid)
        col_counts = [0] * len(grid[0])
        
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 1:
                    row_counts[i] += 1
                    col_counts[j] += 1
        
        result = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 1:
                    result += (row_counts[i] - 1) * (col_counts[j] - 1)
        
        return result