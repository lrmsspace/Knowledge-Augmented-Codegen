# Source: https://leetcode.com/problems/shortest-path-in-a-weighted-tree/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n and an undirected, weighted tree rooted at node 1 with n nodes numbered from 1 to n. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an undirected edge from node ui to vi with weight wi.
#
# You are also given a 2D integer array queries of length q, where each queries[i] is either:
#
#
# 	[1, u, v, w'] – Update the weight of the edge between nodes u and v to w', where (u, v) is guaranteed to be an edge present in edges.
# 	[2, x] – Compute the shortest path distance from the root node 1 to node x.
#
#
# Return an integer array answer, where answer[i] is the shortest path distance from node 1 to x for the ith query of [2, x].
#
# Example:
# Input: n = 2, edges = [[1,2,7]], queries = [[2,2],[1,1,2,4],[2,2]]
#
# Output: [7,4]
#
# Explanation:
#
#
#
#
# 	Query [2,2]: The shortest path from root node 1 to node 2 is 7.
# 	Query [1,1,2,4]: The weight of edge (1,2) changes from 7 to 4.
# 	Query [2,2]: The shortest path from root node 1 to node 2 is 4.
#
# Constraints:
# 1 <= n <= 105
# 	edges.length == n - 1
# 	edges[i] == [ui, vi, wi]
# 	1 <= ui, vi <= n
# 	1 <= wi <= 104
# 	The input is generated such that edges represents a valid tree.
# 	1 <= queries.length == q <= 105
# 	queries[i].length == 2 or 4
# 	
# 		queries[i] == [1, u, v, w'] or,
# 		queries[i] == [2, x]
# 		1 <= u, v, x <= n
# 		(u, v) is always an edge from edges.
# 		1 <= w' <= 104
#
# Helpful references (internal KB):
# - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
#   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
#   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
#   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
#   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
#   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
# - 0-1 BFS (graph, deque, 01-bfs, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
#   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
#   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
#   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
#   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
# - Depth First Search (tree, graph, dfs)
#   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
#   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
#   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
#   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
#   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def treeQueries(self, n, edges, queries):
        """
        :type n: int
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        # Build the tree as an adjacency list
        tree = defaultdict(list)
        for u, v, w in edges:
            tree[u].append((v, w))
            tree[v].append((u, w))

        # Function to perform DFS and calculate distances from the root
        def dfs(node, parent, dist):
            for neighbor, weight in tree[node]:
                if neighbor != parent:
                    dist[neighbor] = dist[node] + weight
                    dfs(neighbor, node, dist)

        # Calculate initial distances from the root node (1)
        dist = [0] * (n + 1)
        dfs(1, -1, dist)

        # Process queries
        answer = []
        for query in queries:
            if query[0] == 1:
                # Update edge weight
                _, u, v, w = query
                # Find the current weight of the edge (u, v)
                for i in range(len(tree[u])):
                    if tree[u][i][0] == v:
                        old_weight = tree[u][i][1]
                        tree[u][i] = (v, w)  # Update weight
                        break
                for i in range(len(tree[v])):
                    if tree[v][i][0] == u:
                        tree[v][i] = (u, w)  # Update weight
                        break
                # Update distances using BFS from the root node
                queue = deque([1])
                visited = [False] * (n + 1)
                visited[1] = True
                while queue:
                    current = queue.popleft()
                    for neighbor, weight in tree[current]:
                        if not visited[neighbor]:
                            visited[neighbor] = True
                            dist[neighbor] = dist[current] + weight
                            queue.append(neighbor)
            else:
                # Query shortest path from root to x
                _, x = query
                answer.append(dist[x])

        return answer