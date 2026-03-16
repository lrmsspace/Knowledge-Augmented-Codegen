# Source: https://leetcode.com/problems/check-if-matrix-is-x-matrix/   |   Difficulty: Easy
#
# Problem Description:
# A square matrix is said to be an X-Matrix if both of the following conditions hold:
#
#
# 	All the elements in the diagonals of the matrix are non-zero.
# 	All other elements are 0.
#
#
# Given a 2D integer array grid of size n x n representing a square matrix, return true if grid is an X-Matrix. Otherwise, return false.
#
# Example:
# Input: grid = [[2,0,0,1],[0,3,1,0],[0,5,2,0],[4,0,0,2]]
# Output: true
# Explanation: Refer to the diagram above. 
# An X-Matrix should have the green elements (diagonals) be non-zero and the red elements be 0.
# Thus, grid is an X-Matrix.
#
# Constraints:
# n == grid.length == grid[i].length
# 	3 <= n <= 100
# 	0 <= grid[i][j] <= 105
#
# Helpful references (internal KB):
# - Finding the rank of a matrix (matrix, simulation, enumeration)
#   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
#   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
#   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
#   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
#   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
# - Calculating the determinant of a matrix by Gauss (matrix, number, simulation, counting)
#   • When to use: When needing to compute the determinant of a square matrix, especially when Gaussian elimination is a familiar or efficient approach. It is suitable for matrices where direct cofactor expansion is computationally too expensive.
#   • Idea: This algorithm computes the determinant of a square matrix by transforming it into an upper triangular form using Gaussian elimination. The determinant is the product of diagonal elements, adjusted by a sign factor from row swaps, with O(N^3) complexity.
#   • Invariants: Before processing column 'k', all elements A[i][j] where i > j and j < k are zero.; The determinant of the current matrix, multiplied by (-1)^swaps, equals the original matrix's determinant.
#   • Tips: Track the number of row swaps to correctly determine the determinant's sign.; Pivot selection can improve numerical stability, especially with floating-point numbers.
#   • Pitfalls: Forgetting to adjust the sign after row exchanges.; Division by zero if a pivot element is zero, requiring a row swap.
# - Calculating the determinant using Kraut method in O(N^3) (matrix, enumeration)
#   • When to use: Use this method to compute the determinant of a square matrix efficiently by decomposing it into lower and upper triangular matrices. It is suitable for problems requiring O(N^3) complexity for matrix operations.
#   • Idea: The Kraut method computes the determinant of a square matrix by first decomposing it into a lower triangular matrix (L) and an upper triangular matrix (U), such that A = LU. The determinant is then the product of the diagonal elements of L and U, achieving O(N^3) time complexity.
#   • Invariants: After processing column k, the first k columns of L and first k rows of U are correctly computed.; For any i <= k and j <= k, the partial sum for A[i][j] from L and U elements up to index min(i,j) is maintained.
#   • Tips: Ensure the input matrix is square for determinant calculation.; The determinant of a triangular matrix is the product of its diagonal elements.
#   • Pitfalls: Division by zero can occur if a pivot element is zero, requiring pivoting strategies.; Floating-point precision issues can accumulate, especially for large matrices.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def checkXMatrix(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: bool
        """
        n = len(grid)
        for i in range(n):
            for j in range(n):
                if (i == j or i + j == n - 1):
                    if grid[i][j] == 0:
                        return False
                else:
                    if grid[i][j] != 0:
                        return False
        return True