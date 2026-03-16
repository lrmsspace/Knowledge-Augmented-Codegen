# Source: https://leetcode.com/problems/longest-special-path/   |   Difficulty: Hard
#
# Problem Description:
# You are given an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1, represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, lengthi] indicates an edge between nodes ui and vi with length lengthi. You are also given an integer array nums, where nums[i] represents the value at node i.
#
# A special path is defined as a downward path from an ancestor node to a descendant node such that all the values of the nodes in that path are unique.
#
# Note that a path may start and end at the same node.
#
# Return an array result of size 2, where result[0] is the length of the longest special path, and result[1] is the minimum number of nodes in all possible longest special paths.
#
# Example:
# Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], nums = [2,1,2,1,3,1]
#
# Output: [6,2]
#
# Explanation:
#
# In the image below, nodes are colored by their corresponding values in nums
#
#
#
# The longest special paths are 2 -> 5 and 0 -> 1 -> 4, both having a length of 6. The minimum number of nodes across all longest special paths is 2.
#
# Constraints:
# 2 <= n <= 5 * 104
# 	edges.length == n - 1
# 	edges[i].length == 3
# 	0 <= ui, vi < n
# 	1 <= lengthi <= 103
# 	nums.length == n
# 	0 <= nums[i] <= 5 * 104
# 	The input is generated such that edges represents a valid tree.
#
# Helpful references (internal KB):
# - Depth-first search (graph, array, dfs, biconnected-components)
#   • When to use: Use when exploring all reachable nodes from a starting point, finding paths, or detecting cycles in a graph. It's suitable for problems requiring a deep, exhaustive search.
#   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically running in O(V + E) time for graphs represented with adjacency lists.
#   • Invariants: Every node `v` is visited exactly once.; When `dfs(G, u, v)` is called, `v` is unvisited and `u` is its immediate predecessor in the current path.
#   • Tips: Maintain a visited set/array to avoid revisiting nodes and infinite loops.; Pass the parent node in recursive calls to correctly identify back-edges for cycle detection.
#   • Pitfalls: Failing to mark nodes as visited can lead to infinite loops in cyclic graphs.; Deep recursion can cause stack overflow errors on large graphs; use an iterative approach if needed.
# - Strong Orientation (graph, tree, dfs)
#   • When to use: Use this when you need to convert an undirected, bridgeless, and connected graph into a strongly connected directed graph, ensuring reachability between any two vertices.
#   • Idea: This algorithm transforms a bridgeless, connected undirected graph into a strongly connected directed graph by performing a Depth-First Search. It orients DFS tree edges away from the root and back edges towards ancestors, achieving strong connectivity in O(V+E) time.
#   • Invariants: All DFS tree edges discovered so far are oriented from parent to child.; All back edges discovered so far are oriented from child to ancestor.
#   • Tips: Verify the input graph is connected and bridgeless before applying the algorithm.; During DFS, mark visited vertices and track parent-child relationships to distinguish edge types.
#   • Pitfalls: Applying to a graph with bridges will result in a non-strongly connected graph.; Incorrectly identifying or orienting back edges can break the strong connectivity property.
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
    def longestSpecialPath(self, edges, nums):
        """
        :type edges: List[List[int]]
        :type nums: List[int]
        :rtype: List[int]
        """
        from collections import defaultdict

        n = len(nums)
        graph = defaultdict(list)
        for u, v, length in edges:
            graph[u].append((v, length))
            graph[v].append((u, length))

        longest_path = 0
        min_nodes = float('inf')

        def dfs(node, parent, visited):
            nonlocal longest_path, min_nodes
            visited.add(nums[node])
            current_length = 0
            current_nodes = 1

            for neighbor, length in graph[node]:
                if neighbor == parent or nums[neighbor] in visited:
                    continue
                dfs(neighbor, node, visited)
                current_length += length
                current_nodes += 1

            if current_length > longest_path:
                longest_path = current_length
                min_nodes = current_nodes
            elif current_length == longest_path:
                min_nodes = min(min_nodes, current_nodes)

            visited.remove(nums[node])

        dfs(0, -1, set())
        return [longest_path, min_nodes]