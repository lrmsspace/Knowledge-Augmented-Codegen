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
# - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
#   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
#   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
#   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
#   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
#   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
#   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
#   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
#   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
#   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
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
        
        row_index = {num: i for i, num in enumerate(row_order)}
        col_index = {num: i for i, num in enumerate(col_order)}
        
        matrix = [[0] * k for _ in range(k)]
        
        for num in range(1, k + 1):
            r, c = row_index[num], col_index[num]
            matrix[r][c] = num
        
        return matrix