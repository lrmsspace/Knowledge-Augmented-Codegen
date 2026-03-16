# Source: https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n integer matrix grid​​​.
#
# A rhombus sum is the sum of the elements that form the border of a regular rhombus shape in grid​​​. The rhombus must have the shape of a square rotated 45 degrees with each of the corners centered in a grid cell. Below is an image of four valid rhombus shapes with the corresponding colored cells that should be included in each rhombus sum:
#
# Note that the rhombus can have an area of 0, which is depicted by the purple rhombus in the bottom right corner.
#
# Return the biggest three distinct rhombus sums in the grid in descending order. If there are less than three distinct values, return all of them.
#
# Example:
# Input: grid = [[3,4,5,1,3],[3,3,4,2,3],[20,30,200,40,10],[1,5,5,4,1],[4,3,2,2,5]]
# Output: [228,216,211]
# Explanation: The rhombus shapes for the three biggest distinct rhombus sums are depicted above.
# - Blue: 20 + 3 + 200 + 5 = 228
# - Red: 200 + 2 + 10 + 4 = 216
# - Green: 5 + 200 + 4 + 2 = 211
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 50
# 	1 <= grid[i][j] <= 105
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Sqrt Decomposition (array, enumeration, difference-array)
#   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
#   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
#   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
#   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
#   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getBiggestThree(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: List[int]
        """
        m, n = len(grid), len(grid[0])
        rhombus_sums = set()

        for i in range(m):
            for j in range(n):
                # Rhombus of size 0 (single cell)
                rhombus_sums.add(grid[i][j])

                # Larger rhombuses
                size = 1
                while i - size >= 0 and i + size < m and j - size >= 0 and j + size < n:
                    total = 0
                    # Top to right
                    for k in range(size):
                        total += grid[i - k][j + k]
                    # Right to bottom
                    for k in range(size):
                        total += grid[i + k][j + k]
                    # Bottom to left
                    for k in range(size):
                        total += grid[i + k][j - k]
                    # Left to top
                    for k in range(size):
                        total += grid[i - k][j - k]

                    # Subtract the corners as they were added twice
                    total -= (grid[i - size][j] + grid[i + size][j] + grid[i][j - size] + grid[i][j + size])
                    rhombus_sums.add(total)
                    size += 1

        return sorted(rhombus_sums, reverse=True)[:3]