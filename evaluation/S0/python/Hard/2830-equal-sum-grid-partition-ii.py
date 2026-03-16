# Source: https://leetcode.com/problems/equal-sum-grid-partition-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:
#
#
# 	Each of the two resulting sections formed by the cut is non-empty.
# 	The sum of elements in both sections is equal, or can be made equal by discounting at most one single cell in total (from either section).
# 	If a cell is discounted, the rest of the section must remain connected.
#
#
# Return true if such a partition exists; otherwise, return false.
#
# Note: A section is connected if every cell in it can be reached from any other cell by moving up, down, left, or right through other cells in the section.
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
#
# 	A horizontal cut after the first row gives sums 1 + 4 = 5 and 2 + 3 = 5, which are equal. Thus, the answer is true.
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
        m, n = len(grid), len(grid[0])
        total_sum = sum(sum(row) for row in grid)

        # Check horizontal cuts
        row_sums = [sum(row) for row in grid]
        prefix_sum = 0
        for i in range(m - 1):
            prefix_sum += row_sums[i]
            if self.can_equal_partition(prefix_sum, total_sum - prefix_sum, grid, 0, i, n - 1, True):
                return True

        # Check vertical cuts
        col_sums = [sum(grid[i][j] for i in range(m)) for j in range(n)]
        prefix_sum = 0
        for j in range(n - 1):
            prefix_sum += col_sums[j]
            if self.can_equal_partition(prefix_sum, total_sum - prefix_sum, grid, 0, m - 1, j, False):
                return True

        return False