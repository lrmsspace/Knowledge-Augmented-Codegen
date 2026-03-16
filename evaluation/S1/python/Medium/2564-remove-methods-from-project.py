# Source: https://leetcode.com/problems/remove-methods-from-project/   |   Difficulty: Medium
#
# Problem Description:
# You are maintaining a project that has n methods numbered from 0 to n - 1.
#
# You are given two integers n and k, and a 2D integer array invocations, where invocations[i] = [ai, bi] indicates that method ai invokes method bi.
#
# There is a known bug in method k. Method k, along with any method invoked by it, either directly or indirectly, are considered suspicious and we aim to remove them.
#
# A group of methods can only be removed if no method outside the group invokes any methods within it.
#
# Return an array containing all the remaining methods after removing all the suspicious methods. You may return the answer in any order. If it is not possible to remove all the suspicious methods, none should be removed.
#
# Example:
# Input: n = 4, k = 1, invocations = [[1,2],[0,1],[3,2]]
#
# Output: [0,1,2,3]
#
# Explanation:
#
#
#
# Method 2 and method 1 are suspicious, but they are directly invoked by methods 3 and 0, which are not suspicious. We return all elements without removing anything.
#
# Constraints:
# 1 <= n <= 105
# 	0 <= k <= n - 1
# 	0 <= invocations.length <= 2 * 105
# 	invocations[i] == [ai, bi]
# 	0 <= ai, bi <= n - 1
# 	ai != bi
# 	invocations[i] != invocations[j]
#
# Helpful references (internal KB):
# - Search for connected components in a graph (stack, graph, dfs, recursion)
#   • When to use: Use when the goal is to identify distinct groups of interconnected nodes within a graph, or to find all nodes reachable from a specific starting point.
#   • Idea: Depth-First Search (DFS) explores a graph by traversing as far as possible along each branch before backtracking. It efficiently finds connected components by visiting all reachable nodes from an unvisited starting point, typically with O(V+E) time complexity.
#   • Invariants: All nodes in the current DFS path from the start node to the current node are on the recursion stack.; Any node marked as visited will not be re-processed by the current DFS call.
#   • Tips: Maintain a 'visited' status for each node to prevent cycles and redundant work.; Iterate through all nodes and start DFS if a node is unvisited to find all components.
#   • Pitfalls: Excessive recursion depth can lead to stack overflow errors for large graphs.; Forgetting to mark nodes as visited results in infinite loops in cyclic graphs.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Minimum Enclosing Circle (array, geometry, randomized, recursion)
#   • When to use: Use when finding the smallest circle that contains a given set of 2D points. It provides an expected linear time solution for this fundamental geometric problem.
#   • Idea: Welzl's algorithm finds the unique minimum enclosing circle for a set of points using a randomized incremental approach. It achieves an expected time complexity of O(N).
#   • Invariants: The current candidate circle `C` encloses all points `p_1, ..., p_i` processed so far.; If `p_i` is not contained in `C_{i-1}`, then `p_i` must lie on the boundary of `C_i`.
#   • Tips: Randomly permute input points to ensure expected O(N) performance.; The MEC is uniquely determined by either two points forming a diameter or three points on its boundary.
#   • Pitfalls: Not randomizing the input can lead to a worst-case O(N^3) performance.; Floating-point precision issues can cause incorrect boundary checks or point containment tests.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def remainingMethods(self, n, k, invocations):
        """
        :type n: int
        :type k: int
        :type invocations: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        # Build the graph and in-degree count
        graph = defaultdict(list)
        in_degree = [0] * n
        
        for a, b in invocations:
            graph[a].append(b)
            in_degree[b] += 1

        # Find all methods reachable from k using DFS
        suspicious = set()
        stack = [k]
        
        while stack:
            node = stack.pop()
            if node not in suspicious:
                suspicious.add(node)
                for neighbor in graph[node]:
                    stack.append(neighbor)

        # Check if any suspicious method is invoked by a non-suspicious method
        for method in range(n):
            if method not in suspicious:
                for neighbor in graph[method]:
                    if neighbor in suspicious:
                        return list(range(n))  # Cannot remove any methods

        # Return remaining methods
        return [method for method in range(n) if method not in suspicious]