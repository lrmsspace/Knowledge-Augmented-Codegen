# Source: https://leetcode.com/problems/build-a-matrix-with-conditions/   |   Difficulty: Hard
#
# Problem Description:
# You are given a positive integer k. You are also given:
#
#
# 	a 2D integer array rowConditions of size n where rowConditions[i] = [abovei, belowi], and
# 	a 2D integer array colConditions of size m where colConditions[i] = [lefti, righti].
#
#
# The two arrays contain integers from 1 to k.
#
# You have to build a k x k matrix that contains each of the numbers from 1 to k exactly once. The remaining cells should have the value 0.
#
# The matrix should also satisfy the following conditions:
#
#
# 	The number abovei should appear in a row that is strictly above the row at which the number belowi appears for all i from 0 to n - 1.
# 	The number lefti should appear in a column that is strictly left of the column at which the number righti appears for all i from 0 to m - 1.
#
#
# Return any matrix that satisfies the conditions. If no answer exists, return an empty matrix.
#
# Example:
# Input: k = 3, rowConditions = [[1,2],[3,2]], colConditions = [[2,1],[3,2]]
# Output: [[3,0,0],[0,0,1],[0,2,0]]
# Explanation: The diagram above shows a valid example of a matrix that satisfies all the conditions.
# The row conditions are the following:
# - Number 1 is in row 1, and number 2 is in row 2, so 1 is above 2 in the matrix.
# - Number 3 is in row 0, and number 2 is in row 2, so 3 is above 2 in the matrix.
# The column conditions are the following:
# - Number 2 is in column 1, and number 1 is in column 2, so 2 is left of 1 in the matrix.
# - Number 3 is in column 0, and number 2 is in column 1, so 3 is left of 2 in the matrix.
# Note that there may be multiple correct answers.
#
# Constraints:
# 2 <= k <= 400
# 	1 <= rowConditions.length, colConditions.length <= 104
# 	rowConditions[i].length == colConditions[i].length == 2
# 	1 <= abovei, belowi, lefti, righti <= k
# 	abovei != belowi
# 	lefti != righti
#
# Helpful references (internal KB):
# - Topological Sorting (graph, array, dfs, topo)
#   • When to use: Use for graph or tree traversal, pathfinding, cycle detection, or topological sorting in DAGs. It's also suitable for exploring all states in a search space.
#   • Idea: DFS explores as far as possible along each branch before backtracking, typically using recursion or an explicit stack. Topological sort orders nodes in a DAG such that for every directed edge u -> v, u comes before v, achievable with DFS in O(V+E) time.
#   • Invariants: All nodes reachable from the current path have been explored or are in the recursion stack.; A node is marked 'visited' only after all its descendants have been fully explored.
#   • Tips: Use a visited set/array to prevent infinite loops in graphs and redundant computations.; Recursion is natural for DFS, but an explicit stack can avoid recursion depth limits.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect results.; Exceeding recursion depth limits for very deep graphs or trees.
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def buildMatrix(self, k, rowConditions, colConditions):
        """
        :type k: int
        :type rowConditions: List[List[int]]
        :type colConditions: List[List[int]]
        :rtype: List[List[int]]
        """
        from collections import defaultdict, deque

        def topological_sort(conditions):
            graph = defaultdict(list)
            in_degree = {i: 0 for i in range(1, k + 1)}

            for u, v in conditions:
                graph[u].append(v)
                in_degree[v] += 1

            queue = deque([node for node in in_degree if in_degree[node] == 0])
            topo_order = []

            while queue:
                node = queue.popleft()
                topo_order.append(node)
                for neighbor in graph[node]:
                    in_degree[neighbor] -= 1
                    if in_degree[neighbor] == 0:
                        queue.append(neighbor)

            return topo_order if len(topo_order) == k else []

        row_order = topological_sort(rowConditions)
        col_order = topological_sort(colConditions)

        if not row_order or not col_order:
            return []

        position = {num: (row_order.index(num), col_order.index(num)) for num in range(1, k + 1)}
        matrix = [[0] * k for _ in range(k)]

        for num, (r, c) in position.items():
            matrix[r][c] = num

        return matrix