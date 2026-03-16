# Source: https://leetcode.com/problems/construct-2d-grid-matching-graph-layout/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D integer array edges representing an undirected graph having n nodes, where edges[i] = [ui, vi] denotes an edge between nodes ui and vi.
#
# Construct a 2D grid that satisfies these conditions:
#
#
# 	The grid contains all nodes from 0 to n - 1 in its cells, with each node appearing exactly once.
# 	Two nodes should be in adjacent grid cells (horizontally or vertically) if and only if there is an edge between them in edges.
#
#
# It is guaranteed that edges can form a 2D grid that satisfies the conditions.
#
# Return a 2D integer array satisfying the conditions above. If there are multiple solutions, return any of them.
#
# Example:
# Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]]
#
# Output: [[3,1],[2,0]]
#
# Explanation:
#
# Constraints:
# 2 <= n <= 5 * 104
# 	1 <= edges.length <= 105
# 	edges[i] = [ui, vi]
# 	0 <= ui < vi < n
# 	All the edges are distinct.
# 	The input is generated such that edges can form a 2D grid that satisfies the conditions.
#
# Helpful references (internal KB):
# - Multi source BFS (queue, graph, multi-source-bfs, bfs)
#   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
#   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
#   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
#   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
#   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
# - Undirected Graphs (graph, array, simulation)
#   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
#   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
#   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
#   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
#   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
# - Depth First Search (graph, dfs, topo)
#   • When to use: Use DFS to explore all reachable vertices from a starting point, find paths, detect cycles, or perform topological sorting on directed acyclic graphs.
#   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically runs in O(V + E) time for graphs represented with adjacency lists, where V is the number of vertices and E is the number of edges.
#   • Invariants: Every node is visited at most once.; The `visited` set accurately reflects nodes currently in the recursion stack or fully explored.
#   • Tips: Always use a visited set to avoid infinite loops in cyclic graphs.; For topological sort, add nodes to a list after visiting all their neighbors.
#   • Pitfalls: Risk of stack overflow for very deep graphs or trees.; Failing to mark nodes as visited before recursive calls can lead to re-processing.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def constructGridLayout(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[List[int]]
        """
        from collections import defaultdict, deque

        # Build the graph
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        # Find the degree of each node
        degree = {i: len(graph[i]) for i in range(n)}

        # Start BFS from a node with degree 2 (corner node)
        start_node = next(i for i in range(n) if degree[i] == 2)
        visited = set([start_node])
        queue = deque([start_node])
        layout = [[-1] * n for _ in range(n)]

        # BFS to fill the grid
        while queue:
            node = queue.popleft()
            x, y = divmod(node, n)  # Get grid coordinates
            layout[x][y] = node

            for neighbor in graph[node]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)

        return layout