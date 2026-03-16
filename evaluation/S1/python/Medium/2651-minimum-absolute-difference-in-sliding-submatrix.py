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
# Helpful references (internal KB):
# - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
#   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
#   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
#   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
#   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
#   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Minimum spanning tree - Prim's algorithm (graph, heap, array, mst-prim, greedy, heap-select)
#   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, weighted graph. It is efficient for both dense graphs (O(V^2)) and sparse graphs (O(E log V)) depending on the implementation.
#   • Idea: Prim's algorithm is a greedy algorithm that builds an MST by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside the tree. It has a time complexity of O(V^2) for dense graphs using an adjacency matrix or O(E log V) for sparse graphs using a priority queue.
#   • Invariants: All selected vertices and edges form a connected component of the final MST.; For any unselected vertex `v`, `min_e[v]` stores the minimum weight of an edge connecting `v` to the currently selected component.
#   • Tips: For dense graphs, an O(V^2) implementation using an an adjacency matrix and simple array scans is efficient.; For sparse graphs, use a priority queue (min-heap) with an adjacency list to achieve O(E log V) complexity.
#   • Pitfalls: Incorrectly updating the `min_e` array or priority queue entries can lead to an incorrect MST or performance issues.; Forgetting to mark vertices as 'selected' can lead to cycles or infinite loops.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

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
            sorted_rows = [sorted(grid[i + x][0:k]) for x in range(k)]

            for j in range(n - k + 1):
                if j > 0:
                    for x in range(k):
                        row = sorted_rows[x]
                        old_val = grid[i + x][j - 1]
                        new_val = grid[i + x][j + k - 1]
                        row.remove(old_val)
                        bisect.insort_left(row, new_val)

                merged = []
                for row in sorted_rows:
                    merged.extend(row)
                merged.sort()

                min_diff = float('inf')
                for x in range(1, len(merged)):
                    if merged[x] != merged[x - 1]:
                        min_diff = min(min_diff, merged[x] - merged[x - 1])

                ans[i][j] = min_diff if min_diff != float('inf') else 0

        return ans