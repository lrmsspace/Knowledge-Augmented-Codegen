# Source: https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/   |   Difficulty: Medium
#
# Problem Description:
# Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.
#
# A grid is said to be valid if all the cells above the main diagonal are zeros.
#
# Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.
#
# The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).
#
# Example:
# Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
# Output: 3
#
# Constraints:
# n == grid.length == grid[i].length
# 	1 <= n <= 200
# 	grid[i][j] is either 0 or 1
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minSwaps(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        # 计算每行末尾连续0的数量
        trailing_zeros = []
        for row in grid:
            count = 0
            for j in range(n - 1, -1, -1):
                if row[j] == 0:
                    count += 1
                else:
                    break
            trailing_zeros.append(count)

        swaps = 0
        for i in range(n):
            required_zeros = n - 1 - i
            # 找到满足条件的行
            j = i
            while j < n and trailing_zeros[j] < required_zeros:
                j += 1
            
            if j == n:  # 没有找到满足条件的行
                return -1
            
            # 将找到的行交换到位置i
            while j > i:
                trailing_zeros[j], trailing_zeros[j - 1] = trailing_zeros[j - 1], trailing_zeros[j]
                j -= 1
                swaps += 1

        return swaps