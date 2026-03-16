# Source: https://leetcode.com/problems/largest-plus-sign/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n. You have an n x n binary grid grid with all values initially 1's except for some indices given in the array mines. The ith element of the array mines is defined as mines[i] = [xi, yi] where grid[xi][yi] == 0.
#
# Return the order of the largest axis-aligned plus sign of 1's contained in grid. If there is none, return 0.
#
# An axis-aligned plus sign of 1's of order k has some center grid[r][c] == 1 along with four arms of length k - 1 going up, down, left, and right, and made of 1's. Note that there could be 0's or 1's beyond the arms of the plus sign, only the relevant area of the plus sign is checked for 1's.
#
# Example:
# Input: n = 5, mines = [[4,2]]
# Output: 2
# Explanation: In the above grid, the largest plus sign can only be of order 2. One of them is shown.
#
# Constraints:
# 1 <= n <= 500
# 	1 <= mines.length <= 5000
# 	0 <= xi, yi < n
# 	All the pairs (xi, yi) are unique.
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
    def orderOfLargestPlusSign(self, n, mines):
        """
        :type n: int
        :type mines: List[List[int]]
        :rtype: int
        """
        grid = [[1] * n for _ in range(n)]
        for x, y in mines:
            grid[x][y] = 0

        left = [[0] * n for _ in range(n)]
        right = [[0] * n for _ in range(n)]
        up = [[0] * n for _ in range(n)]
        down = [[0] * n for _ in range(n)]

        for i in range(n):
            count = 0
            for j in range(n):
                count = count + 1 if grid[i][j] == 1 else 0
                left[i][j] = count
            count = 0
            for j in range(n - 1, -1, -1):
                count = count + 1 if grid[i][j] == 1 else 0
                right[i][j] = count

        for j in range(n):
            count = 0
            for i in range(n):
                count = count + 1 if grid[i][j] == 1 else 0
                up[i][j] = count
            count = 0
            for i in range(n - 1, -1, -1):
                count = count + 1 if grid[i][j] == 1 else 0
                down[i][j] = count

        max_order = 0
        for i in range(n):
            for j in range(n):
                order = min(left[i][j], right[i][j], up[i][j], down[i][j])
                max_order = max(max_order, order)

        return max_order