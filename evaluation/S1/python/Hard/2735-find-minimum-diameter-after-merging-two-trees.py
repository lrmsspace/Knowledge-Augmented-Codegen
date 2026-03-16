# Source: https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/   |   Difficulty: Hard
#
# Problem Description:
# There exist two undirected trees with n and m nodes, numbered from 0 to n - 1 and from 0 to m - 1, respectively. You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.
#
# You must connect one node from the first tree with another node from the second tree with an edge.
#
# Return the minimum possible diameter of the resulting tree.
#
# The diameter of a tree is the length of the longest path between any two nodes in the tree.
#
# Example:
# Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
#
# Output: 3
#
# Explanation:
#
# We can obtain a tree of diameter 3 by connecting node 0 from the first tree with any node from the second tree.
#
# Constraints:
# 1 <= n, m <= 105
# 	edges1.length == n - 1
# 	edges2.length == m - 1
# 	edges1[i].length == edges2[i].length == 2
# 	edges1[i] = [ai, bi]
# 	0 <= ai, bi < n
# 	edges2[i] = [ui, vi]
# 	0 <= ui, vi < m
# 	The input is generated such that edges1 and edges2 represent valid trees.
#
# Helpful references (internal KB):
# - Depth First Search (tree, graph, dfs)
#   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
#   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
#   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
#   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
#   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
# - Lowest Common Ancestor (tree, array, dfs)
#   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
#   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
#   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
#   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
#   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
# - Finding the Eulerian path in O(M) (graph, eulerian-circuit, dfs)
#   • When to use: Use when you need to find a path or cycle that traverses every edge exactly once in a given graph. It's applicable when specific vertex degree conditions are met for path or cycle existence.
#   • Idea: This algorithm constructs an Eulerian path or cycle by first verifying vertex degree conditions and graph connectivity, then performing a recursive DFS-like traversal to build the path. It achieves a time complexity of O(M), where M is the number of edges.
#   • Invariants: Every edge in the constructed path has been traversed exactly once.; All edges incident to the current vertex have been explored or are part of the remaining graph.
#   • Tips: Verify graph connectivity, ignoring isolated vertices.; For an Eulerian path, ensure exactly two vertices have odd degrees.
#   • Pitfalls: Failing to check graph connectivity before starting.; Incorrectly counting odd degree vertices for path vs. cycle.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumDiameterAfterMerge(self, edges1, edges2):
        """
        :type edges1: List[List[int]]
        :type edges2: List[List[int]]
        :rtype: int
        """
        def build_graph(edges):
            graph = {}
            for u, v in edges:
                if u not in graph:
                    graph[u] = []
                if v not in graph:
                    graph[v] = []
                graph[u].append(v)
                graph[v].append(u)
            return graph

        def bfs(start, graph):
            visited = set()
            queue = [(start, 0)]
            visited.add(start)
            farthest_node = start
            max_distance = 0

            while queue:
                node, distance = queue.pop(0)
                if distance > max_distance:
                    max_distance = distance
                    farthest_node = node

                for neighbor in graph.get(node, []):
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append((neighbor, distance + 1))

            return farthest_node, max_distance

        # Build graphs from edges
        graph1 = build_graph(edges1)
        graph2 = build_graph(edges2)

        # Find the diameter of the first tree
        arbitrary_node1 = next(iter(graph1))
        farthest_node1, _ = bfs(arbitrary_node1, graph1)
        _, diameter1 = bfs(farthest_node1, graph1)

        # Find the diameter of the second tree
        arbitrary_node2 = next(iter(graph2))
        farthest_node2, _ = bfs(arbitrary_node2, graph2)
        _, diameter2 = bfs(farthest_node2, graph2)

        # The minimum diameter after merging is the maximum of the two diameters plus one for the new edge
        return max(diameter1, diameter2) + 1