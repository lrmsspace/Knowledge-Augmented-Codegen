# Source: https://leetcode.com/problems/critical-connections-in-a-network/   |   Difficulty: Hard
#
# Problem Description:
# There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.
#
# A critical connection is a connection that, if removed, will make some servers unable to reach some other server.
#
# Return all critical connections in the network in any order.
#
# Example:
# Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
# Output: [[1,3]]
# Explanation: [[3,1]] is also accepted.
#
# Constraints:
# 2 <= n <= 105
# 	n - 1 <= connections.length <= 105
# 	0 <= ai, bi <= n - 1
# 	ai != bi
# 	There are no repeated connections.
#
# Helpful references (internal KB):
# - Finding bridges in a graph in O(N+M) (graph, dfs)
#   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
#   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
#   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
#   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
#   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
# - Strong Orientation (graph, dfs, biconnected-components)
#   • When to use: Use when you need to identify maximal subgraphs where removing any single vertex does not disconnect the subgraph. This is crucial for analyzing network robustness and fault tolerance.
#   • Idea: This algorithm decomposes a graph into maximal 2-vertex-connected subgraphs, meaning removing any single vertex does not disconnect them. It uses DFS to identify articulation points and bridges, achieving O(V+E) time complexity.
#   • Invariants: All edges on the DFS stack form part of a potential BCC.; A vertex's low-link value is the minimum discovery time reachable from it (including itself) through its DFS subtree and at most one back-edge.
#   • Tips: Maintain discovery times and low-link values for each vertex.; Use a stack to store edges or vertices of the current DFS path.
#   • Pitfalls: Incorrectly calculating low-link values, especially for back-edges.; Missing the root node articulation point condition (at least two children in DFS tree).
# - Search for connected components in a graph (stack, graph, dfs, recursion)
#   • When to use: Use when the goal is to identify distinct groups of interconnected nodes within a graph, or to find all nodes reachable from a specific starting point.
#   • Idea: Depth-First Search (DFS) explores a graph by traversing as far as possible along each branch before backtracking. It efficiently finds connected components by visiting all reachable nodes from an unvisited starting point, typically with O(V+E) time complexity.
#   • Invariants: All nodes in the current DFS path from the start node to the current node are on the recursion stack.; Any node marked as visited will not be re-processed by the current DFS call.
#   • Tips: Maintain a 'visited' status for each node to prevent cycles and redundant work.; Iterate through all nodes and start DFS if a node is unvisited to find all components.
#   • Pitfalls: Excessive recursion depth can lead to stack overflow errors for large graphs.; Forgetting to mark nodes as visited results in infinite loops in cyclic graphs.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def criticalConnections(self, n, connections):
        """
        :type n: int
        :type connections: List[List[int]]
        :rtype: List[List[int]]
        """
        from collections import defaultdict

        graph = defaultdict(list)
        for u, v in connections:
            graph[u].append(v)
            graph[v].append(u)

        disc = [-1] * n
        low = [-1] * n
        time = [0]  # Mutable object to keep track of discovery time
        bridges = []

        def dfs(u, parent):
            disc[u] = low[u] = time[0]
            time[0] += 1

            for v in graph[u]:
                if disc[v] == -1:  # If v is not visited
                    dfs(v, u)
                    low[u] = min(low[u], low[v])
                    if low[v] > disc[u]:  # Found a bridge
                        bridges.append([u, v])
                elif v != parent:  # Update low value for back edge
                    low[u] = min(low[u], disc[v])

        for i in range(n):
            if disc[i] == -1:
                dfs(i, -1)

        return bridges