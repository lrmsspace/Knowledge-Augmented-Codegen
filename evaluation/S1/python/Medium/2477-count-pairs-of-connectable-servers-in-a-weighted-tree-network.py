# Source: https://leetcode.com/problems/count-pairs-of-connectable-servers-in-a-weighted-tree-network/   |   Difficulty: Medium
#
# Problem Description:
# You are given an unrooted weighted tree with n vertices representing servers numbered from 0 to n - 1, an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional edge between vertices ai and bi of weight weighti. You are also given an integer signalSpeed.
#
# Two servers a and b are connectable through a server c if:
#
#
# 	a < b, a != c and b != c.
# 	The distance from c to a is divisible by signalSpeed.
# 	The distance from c to b is divisible by signalSpeed.
# 	The path from c to b and the path from c to a do not share any edges.
#
#
# Return an integer array count of length n where count[i] is the number of server pairs that are connectable through the server i.
#
# Example:
# Input: edges = [[0,1,1],[1,2,5],[2,3,13],[3,4,9],[4,5,2]], signalSpeed = 1
# Output: [0,4,6,6,4,0]
# Explanation: Since signalSpeed is 1, count[c] is equal to the number of pairs of paths that start at c and do not share any edges.
# In the case of the given path graph, count[c] is equal to the number of servers to the left of c multiplied by the servers to the right of c.
#
# Constraints:
# 2 <= n <= 1000
# 	edges.length == n - 1
# 	edges[i].length == 3
# 	0 <= ai, bi < n
# 	edges[i] = [ai, bi, weighti]
# 	1 <= weighti <= 106
# 	1 <= signalSpeed <= 106
# 	The input is generated such that edges represents a valid tree.
#
# Helpful references (internal KB):
# - Depth-first search (graph, array, dfs, biconnected-components)
#   • When to use: Use when exploring all reachable nodes from a starting point, finding paths, or detecting cycles in a graph. It's suitable for problems requiring a deep, exhaustive search.
#   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically running in O(V + E) time for graphs represented with adjacency lists.
#   • Invariants: Every node `v` is visited exactly once.; When `dfs(G, u, v)` is called, `v` is unvisited and `u` is its immediate predecessor in the current path.
#   • Tips: Maintain a visited set/array to avoid revisiting nodes and infinite loops.; Pass the parent node in recursive calls to correctly identify back-edges for cycle detection.
#   • Pitfalls: Failing to mark nodes as visited can lead to infinite loops in cyclic graphs.; Deep recursion can cause stack overflow errors on large graphs; use an iterative approach if needed.
# - 0-1 BFS (graph, deque, 01-bfs, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
#   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
#   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
#   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
#   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
# - The Inclusion-Exclusion Principle (array, number, counting, sieve)
#   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
#   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
#   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
#   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
#   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countPairsOfConnectableServers(self, edges, signalSpeed):
        """
        :type edges: List[List[int]]
        :type signalSpeed: int
        :rtype: List[int]
        """
        from collections import defaultdict

        n = len(edges) + 1
        graph = defaultdict(list)
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))

        result = [0] * n

        def dfs(node, parent):
            count = [0] * signalSpeed
            count[0] = 1

            for neighbor, weight in graph[node]:
                if neighbor == parent:
                    continue
                child_count = dfs(neighbor, node)

                for i in range(signalSpeed):
                    for j in range(signalSpeed):
                        if (i + j + weight) % signalSpeed == 0:
                            result[node] += count[i] * child_count[j]

                new_count = [0] * signalSpeed
                for i in range(signalSpeed):
                    new_count[(i + weight) % signalSpeed] += child_count[i]

                for i in range(signalSpeed):
                    count[i] += new_count[i]

            return count

        dfs(0, -1)
        return result