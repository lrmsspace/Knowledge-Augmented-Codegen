# Source: https://leetcode.com/problems/shift-2d-grid/   |   Difficulty: Easy
#
# Problem Description:
# Given a 2D grid of size m x n and an integer k. You need to shift the grid k times.
#
# In one shift operation:
#
#
# 	Element at grid[i][j] moves to grid[i][j + 1].
# 	Element at grid[i][n - 1] moves to grid[i + 1][0].
# 	Element at grid[m - 1][n - 1] moves to grid[0][0].
#
#
# Return the 2D grid after applying shift operation k times.
#
# Example:
# Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
# Output: [[9,1,2],[3,4,5],[6,7,8]]
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m <= 50
# 	1 <= n <= 50
# 	-1000 <= grid[i][j] <= 1000
# 	0 <= k <= 100
#
# Helpful references (internal KB):
# - Josephus Problem (number, simulation, recursion)
#   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
#   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
#   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
#   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
#   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
# - Finding the rank of a matrix (matrix, simulation, enumeration)
#   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
#   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
#   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
#   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
#   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
# - Gauss method for solving system of linea (matrix, number, simulation)
#   • When to use: Use when solving systems of linear equations, including those over finite fields (modulo p), to find unique, multiple, or no solutions.
#   • Idea: Gauss-Jordan elimination systematically transforms a system of linear equations into an equivalent, simpler form (row echelon or reduced row echelon) using elementary row operations to find solutions. This process typically has a time complexity of O(N^2 * M) for an N x M matrix.
#   • Invariants: After k steps, the first k columns form an identity submatrix (or a column with 1 at pivot and 0s elsewhere) in the upper-left kxk block.; The system of equations represented by the augmented matrix remains equivalent to the original system.
#   • Tips: Always perform row operations on the augmented matrix (A|b) to ensure consistency.; Choose a pivot with the largest absolute value to improve numerical stability and reduce error propagation.
#   • Pitfalls: Division by zero if a pivot element is zero and no suitable row swap is found.; Numerical instability with floating-point numbers if pivots are very small, leading to precision issues.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def shiftGrid(self, grid, k):
        """
        :type grid: List[List[int]]
        :type k: int
        :rtype: List[List[int]]
        """
        m, n = len(grid), len(grid[0])
        k = k % (m * n)  # Handle cases where k is larger than total elements
        flat_grid = [grid[i][j] for i in range(m) for j in range(n)]  # Flatten the grid
        shifted_grid = flat_grid[-k:] + flat_grid[:-k]  # Shift the grid
        return [shifted_grid[i*n:(i+1)*n] for i in range(m)]  # Reshape back to 2D