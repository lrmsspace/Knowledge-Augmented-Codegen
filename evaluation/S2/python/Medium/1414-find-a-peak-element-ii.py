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
# - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
#   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
#   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
#   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
#   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
#   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
# -  
# Kth order statistic in O(N) (array, quickselect)
#   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without fully sorting the entire data structure. It's particularly useful for large datasets where a full sort is too slow.
#   • Idea: Quickselect is a selection algorithm that finds the Kth smallest element in an unsorted list. It uses a divide-and-conquer approach similar to Quicksort, but only recurses on one side, achieving an average time complexity of O(N).
#   • Invariants: All elements to the left of the pivot are less than or equal to the pivot's value.; All elements to the right of the pivot are greater than or equal to the pivot's value.
#   • Tips: Choose a good pivot strategy, such as a random pivot, to minimize the chance of worst-case performance.; Handle duplicate elements carefully during the partitioning step to ensure correctness.
#   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Deep recursion without tail call optimization can cause stack overflow errors.
# - Discrete Logarithm (array, number, binary-search, mod-exp)
#   • When to use: Use when solving for the exponent 'x' in the modular equation a^x = b (mod m), especially when 'm' is large and a and m are coprime. It's suitable for finding a solution within O(sqrt(m) log m) time.
#   • Idea: This algorithm, also known as Baby-step Giant-step, finds the smallest non-negative integer 'x' satisfying a^x = b (mod m) using a meet-in-the-middle approach. It achieves a time complexity of O(sqrt(m) log m).
#   • Invariants: The map stores (a^q mod m, q) for all baby steps q in [0, n-1].; For each giant step p, a^(np) mod m is correctly computed.
#   • Tips: Choose 'n' as ceil(sqrt(m)) for balanced steps.; Use a hash map to store baby steps for O(1) average lookup.
#   • Pitfalls: Incorrect choice of 'n' can lead to suboptimal time complexity.; Failure to check if 'a' and 'm' are coprime may yield no solution or incorrect results.
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
            if (mid_col == 0 or mat[max_row][mid_col] > mat[max_row][mid_col - 1]) and (mid_col == n - 1 or mat[max_row][mid_col] > mat[max_row][mid_col + 1]):
                return [max_row, mid_col]
            elif mid_col > 0 and mat[max_row][mid_col - 1] > mat[max_row][mid_col]:
                right = mid_col - 1
            else:
                left = mid_col + 1
        return [-1, -1]  # This line should never be reached due to problem constraints