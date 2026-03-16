# Source: https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D binary array grid. You need to find 3 non-overlapping rectangles having non-zero areas with horizontal and vertical sides such that all the 1's in grid lie inside these rectangles.
#
# Return the minimum possible sum of the area of these rectangles.
#
# Note that the rectangles are allowed to touch.
#
# Example:
# Input: grid = [[1,0,1],[1,1,1]]
#
# Output: 5
#
# Explanation:
#
#
#
#
# 	The 1's at (0, 0) and (1, 0) are covered by a rectangle of area 2.
# 	The 1's at (0, 2) and (1, 2) are covered by a rectangle of area 2.
# 	The 1 at (1, 1) is covered by a rectangle of area 1.
#
# Constraints:
# 1 <= grid.length, grid[i].length <= 30
# 	grid[i][j] is either 0 or 1.
# 	The input is generated such that there are at least three 1's in grid.
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
#   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
#   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
#   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
#   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
#   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumSum(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        # Step 1: Identify the positions of all 1's in the grid
        ones_positions = [(i, j) for i in range(len(grid)) for j in range(len(grid[0])) if grid[i][j] == 1]

        # Step 2: Generate all combinations of 3 rectangles that can cover the 1's
        from itertools import combinations

        min_area_sum = float('inf')

        for rects in combinations(ones_positions, 3):
            # Step 3: Calculate the area of the rectangles needed to cover these points
            area_sum = self.calculate_area_sum(rects)
            min_area_sum = min(min_area_sum, area_sum)

        return min_area_sum