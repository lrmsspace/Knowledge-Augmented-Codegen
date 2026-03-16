# Source: https://leetcode.com/problems/largest-local-values-in-a-matrix/   |   Difficulty: Easy
#
# Problem Description:
# You are given an n x n integer matrix grid.
#
# Generate an integer matrix maxLocal of size (n - 2) x (n - 2) such that:
#
#
# 	maxLocal[i][j] is equal to the largest value of the 3 x 3 matrix in grid centered around row i + 1 and column j + 1.
#
#
# In other words, we want to find the largest value in every contiguous 3 x 3 matrix in grid.
#
# Return the generated matrix.
#
# Example:
# Input: grid = [[9,9,8,1],[5,6,2,6],[8,2,6,4],[6,2,2,2]]
# Output: [[9,9],[8,6]]
# Explanation: The diagram above shows the original matrix and the generated matrix.
# Notice that each value in the generated matrix corresponds to the largest value of a contiguous 3 x 3 matrix in grid.
#
# Constraints:
# n == grid.length == grid[i].length
# 	3 <= n <= 100
# 	1 <= grid[i][j] <= 100
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
#   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
#   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
#   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
#   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
#   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
# - Calculating the determinant using Kraut method in O(N^3) (matrix, enumeration)
#   • When to use: Use this method to compute the determinant of a square matrix efficiently by decomposing it into lower and upper triangular matrices. It is suitable for problems requiring O(N^3) complexity for matrix operations.
#   • Idea: The Kraut method computes the determinant of a square matrix by first decomposing it into a lower triangular matrix (L) and an upper triangular matrix (U), such that A = LU. The determinant is then the product of the diagonal elements of L and U, achieving O(N^3) time complexity.
#   • Invariants: After processing column k, the first k columns of L and first k rows of U are correctly computed.; For any i <= k and j <= k, the partial sum for A[i][j] from L and U elements up to index min(i,j) is maintained.
#   • Tips: Ensure the input matrix is square for determinant calculation.; The determinant of a triangular matrix is the product of its diagonal elements.
#   • Pitfalls: Division by zero can occur if a pivot element is zero, requiring pivoting strategies.; Floating-point precision issues can accumulate, especially for large matrices.
# - Placing Bishops on a Chessboard (array, counting, dp-2d)
#   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
#   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
#   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
#   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
#   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def largestLocal(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: List[List[int]]
        """
        n = len(grid)
        maxLocal = [[0] * (n - 2) for _ in range(n - 2)]

        for i in range(1, n - 1):
            for j in range(1, n - 1):
                maxLocal[i - 1][j - 1] = max(grid[i + x][j + y] for x in range(-1, 2) for y in range(-1, 2))

        return maxLocal