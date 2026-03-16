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
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
#   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
#   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
#   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
#   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
#   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
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
            indegree = {i: 0 for i in range(1, k + 1)}

            for u, v in conditions:
                graph[u].append(v)
                indegree[v] += 1

            queue = deque([node for node in indegree if indegree[node] == 0])
            order = []

            while queue:
                node = queue.popleft()
                order.append(node)
                for neighbor in graph[node]:
                    indegree[neighbor] -= 1
                    if indegree[neighbor] == 0:
                        queue.append(neighbor)

            return order if len(order) == k else None

        row_order = topological_sort(rowConditions)
        col_order = topological_sort(colConditions)

        if row_order is None or col_order is None:
            return []

        position = {num: (row_order.index(num), col_order.index(num)) for num in range(1, k + 1)}
        matrix = [[0] * k for _ in range(k)]

        for num in range(1, k + 1):
            r, c = position[num]
            matrix[r][c] = num

        return matrix