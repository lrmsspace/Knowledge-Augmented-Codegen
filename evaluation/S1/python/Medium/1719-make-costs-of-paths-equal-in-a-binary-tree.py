# Source: https://leetcode.com/problems/make-costs-of-paths-equal-in-a-binary-tree/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n representing the number of nodes in a perfect binary tree consisting of nodes numbered from 1 to n. The root of the tree is node 1 and each node i in the tree has two children where the left child is the node 2 * i and the right child is 2 * i + 1.
#
# Each node in the tree also has a cost represented by a given 0-indexed integer array cost of size n where cost[i] is the cost of node i + 1. You are allowed to increment the cost of any node by 1 any number of times.
#
# Return the minimum number of increments you need to make the cost of paths from the root to each leaf node equal.
#
# Note:
#
#
# 	A perfect binary tree is a tree where each node, except the leaf nodes, has exactly 2 children.
# 	The cost of a path is the sum of costs of nodes in the path.
#
# Example:
# Input: n = 7, cost = [1,5,2,2,3,3,1]
# Output: 6
# Explanation: We can do the following increments:
# - Increase the cost of node 4 one time.
# - Increase the cost of node 3 three times.
# - Increase the cost of node 7 two times.
# Each path from the root to a leaf will have a total cost of 9.
# The total increments we did is 1 + 3 + 2 = 6.
# It can be shown that this is the minimum answer we can achieve.
#
# Constraints:
# 3 <= n <= 105
# 	n + 1 is a power of 2
# 	cost.length == n
# 	1 <= cost[i] <= 104
#
# Helpful references (internal KB):
# - Depth First Search (tree, graph, dfs)
#   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
#   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
#   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
#   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
#   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
# - Balanced Search Trees (tree, ds, recursion)
#   • When to use: When needing a self-balancing search tree that guarantees logarithmic time complexity for search and insertion operations. Useful for maintaining data in sorted order with consistent performance, especially when frequent updates are expected.
#   • Idea: A 2-3 tree is a self-balancing search tree where every node has either two children (a 2-node) or three children (a 3-node), ensuring all leaves are at the same depth. It guarantees O(log N) time complexity for search, insertion, and deletion operations.
#   • Invariants: All leaves are at the same depth from the root.; Every node is either a 2-node (one key, two children) or a 3-node (two keys, three children).
#   • Tips: Understand the two node types: 2-nodes (one key, two children) and 3-nodes (two keys, three children).; Insertion always starts by finding the leaf position, then propagates splits upwards if a 4-node is formed.
#   • Pitfalls: Incorrectly handling the promotion of keys during node splits can break the tree's structure.; Forgetting to update parent links after a node split or merge operation.
# - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
#   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
#   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
#   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
#   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
#   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minIncrements(self, n, cost):
        """
        :type n: int
        :type cost: List[int]
        :rtype: int
        """
        def dfs(node):
            if node > n:
                return 0, 0  # (max_cost, total_increments)

            left_cost, left_increments = dfs(2 * node)
            right_cost, right_increments = dfs(2 * node + 1)

            max_cost = max(left_cost, right_cost) + cost[node - 1]
            total_increments = left_increments + right_increments
            total_increments += (max_cost - cost[node - 1] - left_cost)
            total_increments += (max_cost - cost[node - 1] - right_cost)

            return max_cost, total_increments

        _, result = dfs(1)
        return result