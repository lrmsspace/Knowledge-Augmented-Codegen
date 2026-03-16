# Source: https://leetcode.com/problems/frog-position-after-t-seconds/   |   Difficulty: Hard
#
# Problem Description:
# Given an undirected tree consisting of n vertices numbered from 1 to n. A frog starts jumping from vertex 1. In one second, the frog jumps from its current vertex to another unvisited vertex if they are directly connected. The frog can not jump back to a visited vertex. In case the frog can jump to several vertices, it jumps randomly to one of them with the same probability. Otherwise, when the frog can not jump to any unvisited vertex, it jumps forever on the same vertex.
#
# The edges of the undirected tree are given in the array edges, where edges[i] = [ai, bi] means that exists an edge connecting the vertices ai and bi.
#
# Return the probability that after t seconds the frog is on the vertex target. Answers within 10-5 of the actual answer will be accepted.
#
# Example:
# Input: n = 7, edges = [[1,2],[1,3],[1,7],[2,4],[2,6],[3,5]], t = 2, target = 4
# Output: 0.16666666666666666 
# Explanation: The figure above shows the given graph. The frog starts at vertex 1, jumping with 1/3 probability to the vertex 2 after second 1 and then jumping with 1/2 probability to vertex 4 after second 2. Thus the probability for the frog is on the vertex 4 after 2 seconds is 1/3 * 1/2 = 1/6 = 0.16666666666666666.
#
# Constraints:
# 1 <= n <= 100
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	1 <= ai, bi <= n
# 	1 <= t <= 50
# 	1 <= target <= n
#
# Helpful references (internal KB):
# - Depth-first search (graph, array, dfs)
#   • When to use: Use when you need to explore as far as possible along each branch before backtracking, such as for finding paths, connected components, or cycles in a graph.
#   • Idea: DFS systematically explores a graph by going as deep as possible along each branch before backtracking. It runs in O(V + E) time and uses O(V) extra space.
#   • Invariants: All vertices reachable from the starting vertex through already explored paths are marked as visited.; When exploring a vertex 'u', all its unvisited neighbors 'v' are either currently being visited or will be visited recursively.
#   • Tips: Use a 'visited' array or set to prevent infinite loops in cyclic graphs.; Recursion stack can be managed explicitly with an iterative approach using a stack.
#   • Pitfalls: Stack overflow errors for deep graphs if implemented purely recursively.; Incorrectly handling visited states can lead to infinite loops or incorrect results.
# - Finding bridges in a graph in O(N+M) (graph, dfs)
#   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
#   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
#   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
#   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
#   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
# - Lowest Common Ancestor (tree, array, dfs)
#   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
#   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
#   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
#   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
#   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def frogPosition(self, n, edges, t, target):
        """
        :type n: int
        :type edges: List[List[int]]
        :type t: int
        :type target: int
        :rtype: float
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        visited = set()
        queue = deque([(1, 1.0)])  # (current_node, probability)
        visited.add(1)

        for _ in range(t):
            size = len(queue)
            for _ in range(size):
                node, prob = queue.popleft()
                unvisited_neighbors = [neighbor for neighbor in graph[node] if neighbor not in visited]

                if not unvisited_neighbors:
                    queue.append((node, prob))  # Stay on the same node
                else:
                    new_prob = prob / len(unvisited_neighbors)
                    for neighbor in unvisited_neighbors:
                        visited.add(neighbor)
                        queue.append((neighbor, new_prob))

        for node, prob in queue:
            if node == target:
                return prob

        return 0.0