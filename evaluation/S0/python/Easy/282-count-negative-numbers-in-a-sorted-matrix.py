# Source: https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/   |   Difficulty: Easy
#
# Problem Description:
# Given a m x n matrix grid which is sorted in non-increasing order both row-wise and column-wise, return the number of negative numbers in grid.
#
# Example:
# Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
# Output: 8
# Explanation: There are 8 negatives number in the matrix.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 100
# 	-100 <= grid[i][j] <= 100
#
#
#  
# Follow up: Could you find an O(n + m) solution?
#

class Solution(object):
    def countNegatives(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        count = 0
        for row in grid:
            for num in row:
                if num < 0:
                    count += 1
        return count