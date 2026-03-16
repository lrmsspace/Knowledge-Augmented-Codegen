# Source: https://leetcode.com/problems/equal-sum-grid-partition-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:
#
#
# 	Each of the two resulting sections formed by the cut is non-empty.
# 	The sum of the elements in both sections is equal.
#
#
# Return true if such a partition exists; otherwise return false.
#
# Example:
# Input: grid = [[1,4],[2,3]]
#
# Output: true
#
# Explanation:
#
#
#
# A horizontal cut between row 0 and row 1 results in two non-empty sections, each with a sum of 5. Thus, the answer is true.
#
# Constraints:
# 1 <= m == grid.length <= 105
# 	1 <= n == grid[i].length <= 105
# 	2 <= m * n <= 105
# 	1 <= grid[i][j] <= 105
#

class Solution(object):
    def canPartitionGrid(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: bool
        """
        total_sum = sum(sum(row) for row in grid)
        if total_sum % 2 != 0:
            return False
        
        half_sum = total_sum // 2
        
        # Check horizontal cuts
        current_sum = 0
        for i in range(len(grid) - 1):
            current_sum += sum(grid[i])
            if current_sum == half_sum:
                return True
        
        # Check vertical cuts
        current_sum = 0
        for j in range(len(grid[0]) - 1):
            current_sum += sum(grid[i][j] for i in range(len(grid)))
            if current_sum == half_sum:
                return True
        
        return False