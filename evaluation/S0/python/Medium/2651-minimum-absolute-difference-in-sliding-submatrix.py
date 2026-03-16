# Source: https://leetcode.com/problems/minimum-absolute-difference-in-sliding-submatrix/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n integer matrix grid and an integer k.
#
# For every contiguous k x k submatrix of grid, compute the minimum absolute difference between any two distinct values within that submatrix.
#
# Return a 2D array ans of size (m - k + 1) x (n - k + 1), where ans[i][j] is the minimum absolute difference in the submatrix whose top-left corner is (i, j) in grid.
#
# Note: If all elements in the submatrix have the same value, the answer will be 0.
# A submatrix (x1, y1, x2, y2) is a matrix that is formed by choosing all cells matrix[x][y] where x1 <= x <= x2 and y1 <= y <= y2.
#
# Example:
# Input: grid = [[1,8],[3,-2]], k = 2
#
# Output: [[2]]
#
# Explanation:
#
#
# 	There is only one possible k x k submatrix: [[1, 8], [3, -2]].
# 	Distinct values in the submatrix are [1, 8, 3, -2].
# 	The minimum absolute difference in the submatrix is |1 - 3| = 2. Thus, the answer is [[2]].
#
# Constraints:
# 1 <= m == grid.length <= 30
# 	1 <= n == grid[i].length <= 30
# 	-105 <= grid[i][j] <= 105
# 	1 <= k <= min(m, n)
#

class Solution(object):
    def minAbsDiff(self, grid, k):
        """
        :type grid: List[List[int]]
        :type k: int
        :rtype: List[List[int]]
        """
        import bisect
        m, n = len(grid), len(grid[0])
        ans = [[0] * (n - k + 1) for _ in range(m - k + 1)]
        
        for i in range(m - k + 1):
            for j in range(n - k + 1):
                vals = []
                for x in range(i, i + k):
                    for y in range(j, j + k):
                        bisect.insort(vals, grid[x][y])
                
                min_diff = float('inf')
                for p in range(1, len(vals)):
                    if vals[p] != vals[p - 1]:
                        min_diff = min(min_diff, vals[p] - vals[p - 1])
                
                ans[i][j] = min_diff if min_diff != float('inf') else 0
        
        return ans