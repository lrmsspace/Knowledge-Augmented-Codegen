# Source: https://leetcode.com/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/   |   Difficulty: Medium
#
# Problem Description:
# You are given a positive integer n representing the number of nodes of a Directed Acyclic Graph (DAG). The nodes are numbered from 0 to n - 1 (inclusive).
#
# You are also given a 2D integer array edges, where edges[i] = [fromi, toi] denotes that there is a unidirectional edge from fromi to toi in the graph.
#
# Return a list answer, where answer[i] is the list of ancestors of the ith node, sorted in ascending order.
#
# A node u is an ancestor of another node v if u can reach v via a set of edges.
#
# Example:
# Input: n = 8, edgeList = [[0,3],[0,4],[1,3],[2,4],[2,7],[3,5],[3,6],[3,7],[4,6]]
# Output: [[],[],[],[0,1],[0,2],[0,1,3],[0,1,2,3,4],[0,1,2,3]]
# Explanation:
# The above diagram represents the input graph.
# - Nodes 0, 1, and 2 do not have any ancestors.
# - Node 3 has two ancestors 0 and 1.
# - Node 4 has two ancestors 0 and 2.
# - Node 5 has three ancestors 0, 1, and 3.
# - Node 6 has five ancestors 0, 1, 2, 3, and 4.
# - Node 7 has four ancestors 0, 1, 2, and 3.
#
# Constraints:
# 1 <= n <= 1000
# 	0 <= edges.length <= min(2000, n * (n - 1) / 2)
# 	edges[i].length == 2
# 	0 <= fromi, toi <= n - 1
# 	fromi != toi
# 	There are no duplicate edges.
# 	The graph is directed and acyclic.
#
# Helpful references (internal KB):
# - Depth-first search (graph, array, dfs, biconnected-components)
#   • When to use: Use when exploring all reachable nodes from a starting point, finding paths, or detecting cycles in a graph. It's suitable for problems requiring a deep, exhaustive search.
#   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically running in O(V + E) time for graphs represented with adjacency lists.
#   • Invariants: Every node `v` is visited exactly once.; When `dfs(G, u, v)` is called, `v` is unvisited and `u` is its immediate predecessor in the current path.
#   • Tips: Maintain a visited set/array to avoid revisiting nodes and infinite loops.; Pass the parent node in recursive calls to correctly identify back-edges for cycle detection.
#   • Pitfalls: Failing to mark nodes as visited can lead to infinite loops in cyclic graphs.; Deep recursion can cause stack overflow errors on large graphs; use an iterative approach if needed.
# - Shortest Paths (graph, topo, dp-1d)
#   • When to use: This algorithm finds the shortest paths from a single source vertex to all other vertices in a directed acyclic graph (DAG) with arbitrary edge weights.
#   • Idea: This algorithm computes single-source shortest paths in a Directed Acyclic Graph (DAG) by processing vertices in topological order, relaxing outgoing edges. It achieves a time complexity of O(V + E).
#   • Invariants: The distance to the source vertex, distTo[s], remains 0 throughout the algorithm.; For any vertex v, distTo[v] always stores the shortest path found so far from s to v.
#   • Tips: First, perform a topological sort on the DAG to determine the processing order.; Initialize all distances to infinity, except the source vertex which is zero.
#   • Pitfalls: Applying this algorithm to a graph containing cycles will yield incorrect results.; An incorrect topological sort order will lead to incorrect shortest path calculations.
# - Finding bridges in a graph in O(N+M) (graph, array, dfs)
#   • When to use: Use this algorithm when you need to identify edges whose removal would increase the number of connected components in an undirected graph. It's suitable for analyzing network robustness or critical connections.
#   • Idea: This algorithm uses Depth First Search (DFS) to find bridges in an undirected graph by tracking discovery times and the lowest reachable discovery time from a node or its descendants. It operates in linear time, O(N+M), where N is the number of vertices and M is the number of edges.
#   • Invariants: For any node `u` currently in the DFS stack, `tin[u]` is its unique discovery time.; For any node `u` and its child `v` in the DFS tree, `low[v]` represents the earliest discovery time reachable from `v`'s subtree (including `v`) using at most one back-edge.
#   • Tips: Initialize discovery times (tin) and lowest reachable times (low) arrays, along with a visited array.; Pass the parent vertex to the DFS function to avoid treating the parent edge as a back-edge.
#   • Pitfalls: Forgetting to pass the parent node or incorrectly handling the parent edge, leading to false bridge detections.; Failing to initialize `low` values correctly, especially for leaf nodes or isolated components.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getAncestors(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[List[int]]
        """
        from collections import defaultdict, deque

        # Build the graph and in-degree count
        graph = defaultdict(list)
        in_degree = [0] * n
        for u, v in edges:
            graph[u].append(v)
            in_degree[v] += 1

        # Initialize ancestors list
        ancestors = [set() for _ in range(n)]

        # Topological sort using Kahn's algorithm
        queue = deque([i for i in range(n) if in_degree[i] == 0])

        while queue:
            node = queue.popleft()
            for neighbor in graph[node]:
                # Add current node's ancestors to neighbor's ancestors
                ancestors[neighbor].update(ancestors[node])
                # Add current node as an ancestor of neighbor
                ancestors[neighbor].add(node)

                # Decrease in-degree and add to queue if it becomes zero
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)

        # Convert sets to sorted lists
        return [sorted(list(anc)) for anc in ancestors]