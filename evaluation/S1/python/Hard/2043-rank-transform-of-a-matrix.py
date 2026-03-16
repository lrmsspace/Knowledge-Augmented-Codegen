# Source: https://leetcode.com/problems/rank-transform-of-a-matrix/   |   Difficulty: Hard
#
# Problem Description:
# Given an m x n matrix, return a new matrix answer where answer[row][col] is the rank of matrix[row][col].
#
# The rank is an integer that represents how large an element is compared to other elements. It is calculated using the following rules:
#
#
# 	The rank is an integer starting from 1.
# 	If two elements p and q are in the same row or column, then:
# 	
# 		If p < q then rank(p) < rank(q)
# 		If p == q then rank(p) == rank(q)
# 		If p > q then rank(p) > rank(q)
# 	
# 	
# 	The rank should be as small as possible.
#
#
# The test cases are generated so that answer is unique under the given rules.
#
# Example:
# Input: matrix = [[1,2],[3,4]]
# Output: [[1,2],[2,3]]
# Explanation:
# The rank of matrix[0][0] is 1 because it is the smallest integer in its row and column.
# The rank of matrix[0][1] is 2 because matrix[0][1] > matrix[0][0] and matrix[0][0] is rank 1.
# The rank of matrix[1][0] is 2 because matrix[1][0] > matrix[0][0] and matrix[0][0] is rank 1.
# The rank of matrix[1][1] is 3 because matrix[1][1] > matrix[0][1], matrix[1][1] > matrix[1][0], and both matrix[0][1] and matrix[1][0] are rank 2.
#
# Constraints:
# m == matrix.length
# 	n == matrix[i].length
# 	1 <= m, n <= 500
# 	-109 <= matrix[row][col] <= 109
#
# Helpful references (internal KB):
# - Mergesort (array, merge-sort)
#   • When to use: Use when a stable, guaranteed O(N log N) time complexity sort is required, especially for large datasets or when external sorting is beneficial. It is also suitable for linked lists where random access is inefficient.
#   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and O(N) space complexity.
#   • Invariants: Before merging, the left subarray `a[lo...mid]` and the right subarray `a[mid+1...hi]` are sorted.; During the merge, `a[lo...k-1]` contains the `k-lo` smallest elements from `aux[lo...hi]` in sorted order.
#   • Tips: Utilize an auxiliary array for merging to maintain stability and simplify the merge logic.; Consider the bottom-up iterative implementation to avoid recursion depth limits and potentially improve cache performance.
#   • Pitfalls: Requires O(N) auxiliary space, which can be a significant concern for memory-constrained environments.; Recursive implementations can lead to stack overflow errors for extremely large input arrays.
# - Finding the rank of a matrix (matrix, simulation, enumeration)
#   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
#   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
#   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
#   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
#   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
# - Finding Bridges Online (graph, tree, union-find, counting)
#   • When to use: Use when you need to dynamically track bridges and 2-edge-connected components in a graph as edges are added. It efficiently updates the graph structure and bridge count in an online fashion.
#   • Idea: This algorithm maintains 2-edge-connected components and bridges in a graph as edges are added, using a Union-Find structure to manage components and a forest to represent the relationships between them. It typically achieves near-amortized constant time per edge addition.
#   • Invariants: Each 2-edge-connected component is represented by a single root in the Union-Find structure.; The set of bridges forms a forest where each node is a 2-edge-connected component.
#   • Tips: Represent 2-edge-connected components using Union-Find for efficient merging.; Maintain a forest where nodes are 2-edge-connected components and edges are bridges.
#   • Pitfalls: Incorrectly identifying when an edge forms a cycle with existing bridges.; Failing to update the bridge count accurately when bridges are removed.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def matrixRankTransform(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[List[int]]
        """
        from collections import defaultdict

        m, n = len(matrix), len(matrix[0])
        value_to_positions = defaultdict(list)

        # Group positions by their values
        for i in range(m):
            for j in range(n):
                value_to_positions[matrix[i][j]].append((i, j))

        # Initialize rank arrays for rows and columns
        row_rank = [0] * m
        col_rank = [0] * n
        answer = [[0] * n for _ in range(m)]

        # Process values in sorted order
        for value in sorted(value_to_positions.keys()):
            positions = value_to_positions[value]
            rank_updates = []

            # Calculate the rank for each position with the current value
            for i, j in positions:
                rank = max(row_rank[i], col_rank[j]) + 1
                rank_updates.append((i, j, rank))

            # Update the ranks after processing all positions with the same value
            for i, j, rank in rank_updates:
                answer[i][j] = rank
                row_rank[i] = max(row_rank[i], rank)
                col_rank[j] = max(col_rank[j], rank)

        return answer