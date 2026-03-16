# Source: https://leetcode.com/problems/disconnect-path-in-a-binary-matrix-by-at-most-one-flip/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed m x n binary matrix grid. You can move from a cell (row, col) to any of the cells (row + 1, col) or (row, col + 1) that has the value 1. The matrix is disconnected if there is no path from (0, 0) to (m - 1, n - 1).
#
# You can flip the value of at most one (possibly none) cell. You cannot flip the cells (0, 0) and (m - 1, n - 1).
#
# Return true if it is possible to make the matrix disconnect or false otherwise.
#
# Note that flipping a cell changes its value from 0 to 1 or from 1 to 0.
#
# Example:
# Input: grid = [[1,1,1],[1,0,0],[1,1,1]]
# Output: true
# Explanation: We can change the cell shown in the diagram above. There is no path from (0, 0) to (2, 2) in the resulting grid.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 1000
# 	1 <= m * n <= 105
# 	grid[i][j] is either 0 or 1.
# 	grid[0][0] == grid[m - 1][n - 1] == 1
#
# Helpful references (internal KB):
# - Maximum flow - Dinic's algorithm (graph, bfs, dfs)
#   • When to use: Use Dinic's algorithm to find the maximum flow from a source to a sink in a flow network. It is efficient for dense graphs and particularly optimized for unit capacity networks.
#   • Idea: Dinic's algorithm computes the maximum flow by repeatedly constructing a layered network using BFS and then finding a blocking flow in this layered network using DFS. It offers a general time complexity of O(V^2 * E) and O(E * sqrt(V)) for unit capacity networks.
#   • Invariants: The flow on any edge (u, v) never exceeds its original capacity.; For any vertex v (excluding source and sink), the sum of flow into v equals the sum of flow out of v.
#   • Tips: Use BFS to construct the layered graph, assigning levels to nodes from the source.; Employ DFS to find augmenting paths within the layered graph, only traversing edges to higher levels.
#   • Pitfalls: Forgetting to update residual capacities for reverse edges, which can prevent finding valid augmenting paths.; Incorrectly constructing the layered graph or level assignments during the BFS phase.
# - Edge connectivity / Vertex connectivity (graph, enumeration)
#   • When to use: Used to quantify a graph's resilience by finding the minimum number of edges or vertices whose removal disconnects it, or separates a specific pair of nodes.
#   • Idea: Edge connectivity is the minimum edges to disconnect a graph, while vertex connectivity is for vertices. Both are often computed using max-flow min-cut theorems, typically in polynomial time.
#   • Invariants: The flow through any edge in the network does not exceed its capacity.; For any intermediate vertex (not source or sink), the total incoming flow equals the total outgoing flow.
#   • Tips: Edge connectivity between two specific vertices can be found using a max-flow min-cut algorithm.; To find global edge connectivity, iterate over all pairs of vertices or use specialized algorithms.
#   • Pitfalls: Confusing edge connectivity (edges) with vertex connectivity (vertices) requirements.; Incorrectly applying max-flow for global connectivity without considering all relevant source-sink pairs.
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
    def isPossibleToCutPath(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: bool
        """
        m, n = len(grid), len(grid[0])
        
        # Early exit if start or end is blocked
        if grid[0][0] == 0 or grid[m-1][n-1] == 0:
            return True
        
        # DP arrays to count paths from start and to end
        dp_start = [[0] * n for _ in range(m)]
        dp_end = [[0] * n for _ in range(m)]
        
        dp_start[0][0] = 1
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    if i > 0:
                        dp_start[i][j] += dp_start[i-1][j]
                    if j > 0:
                        dp_start[i][j] += dp_start[i][j-1]
        
        dp_end[m-1][n-1] = 1
        for i in range(m-1, -1, -1):
            for j in range(n-1, -1, -1):
                if grid[i][j] == 1:
                    if i < m-1:
                        dp_end[i][j] += dp_end[i+1][j]
                    if j < n-1:
                        dp_end[i][j] += dp_end[i][j+1]
        
        total_paths = dp_start[m-1][n-1]
        
        # Check each cell (except start and end) to see if it's a critical cell
        for i in range(m):
            for j in range(n):
                if (i == 0 and j == 0) or (i == m-1 and j == n-1):
                    continue
                if grid[i][j] == 1:
                    paths_through_cell = dp_start[i][j] * dp_end[i][j]
                    if paths_through_cell == total_paths:
                        return True
        
        return False