# Source: https://leetcode.com/problems/find-a-peak-element-ii/   |   Difficulty: Medium
#
# Problem Description:
# A peak element in a 2D grid is an element that is strictly greater than all of its adjacent neighbors to the left, right, top, and bottom.
#
# Given a 0-indexed m x n matrix mat where no two adjacent cells are equal, find any peak element mat[i][j] and return the length 2 array [i,j].
#
# You may assume that the entire matrix is surrounded by an outer perimeter with the value -1 in each cell.
#
# You must write an algorithm that runs in O(m log(n)) or O(n log(m)) time.
#
# Example:
# Input: mat = [[1,4],[3,2]]
# Output: [0,1]
# Explanation: Both 3 and 4 are peak elements so [1,0] and [0,1] are both acceptable answers.
#
# Constraints:
# m == mat.length
# 	n == mat[i].length
# 	1 <= m, n <= 500
# 	1 <= mat[i][j] <= 105
# 	No two adjacent cells are equal.
#
# Helpful references (internal KB):
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
# - Binary search (interval, number, binary-search-answer, recursion)
#   • When to use: When searching for the extremum (maximum or minimum) of a unimodal function over a continuous or discrete interval. It is efficient for functions where direct differentiation or analytical solutions are complex.
#   • Idea: Ternary search is an algorithm that efficiently finds the extremum of a unimodal function within a given interval by repeatedly narrowing the search space. It typically achieves a logarithmic time complexity, O(log N), where N is the interval size.
#   • Invariants: The extremum of the unimodal function always lies within the current search interval [l, r].; The function value at m1 is compared with m2 to narrow the interval while preserving unimodality.
#   • Tips: Ensure the function is strictly unimodal within the search interval.; Handle discrete intervals carefully, especially the stopping condition (r - l) < 3.
#   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Incorrect stopping conditions can lead to infinite loops or suboptimal answers.
# - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
#   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
#   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
#   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
#   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
#   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findPeakGrid(self, mat):
        """
        :type mat: List[List[int]]
        :rtype: List[int]
        """
        m, n = len(mat), len(mat[0])
        left, right = 0, n - 1

        while left <= right:
            mid_col = (left + right) // 2
            max_row = max(range(m), key=lambda r: mat[r][mid_col])

            # Check if the current element is a peak
            if (mid_col == 0 or mat[max_row][mid_col] > mat[max_row][mid_col - 1]) and \
               (mid_col == n - 1 or mat[max_row][mid_col] > mat[max_row][mid_col + 1]):
                return [max_row, mid_col]
            elif mid_col > 0 and mat[max_row][mid_col - 1] > mat[max_row][mid_col]:
                right = mid_col - 1
            else:
                left = mid_col + 1
        return [-1, -1]  # This line should never be reached due to problem constraints