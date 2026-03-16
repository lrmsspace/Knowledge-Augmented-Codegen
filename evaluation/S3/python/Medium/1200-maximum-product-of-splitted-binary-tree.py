# Source: https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, split the binary tree into two subtrees by removing one edge such that the product of the sums of the subtrees is maximized.
#
# Return the maximum product of the sums of the two subtrees. Since the answer may be too large, return it modulo 109 + 7.
#
# Note that you need to maximize the answer before taking the mod and not after taking it.
#
# Example:
# Input: root = [1,2,3,4,5,6]
# Output: 110
# Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)
#
# Constraints:
# The number of nodes in the tree is in the range [2, 5 * 104].
# 	1 <= Node.val <= 104
#
# Helpful references (internal KB):
# - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
#   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
#   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
#   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
#   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
#   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
# - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
#   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
#   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
#   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
#   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
#   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
# - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
#   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
#   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
#   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
#   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
#   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def maxProduct(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        # Step 1: Calculate the total sum of all nodes in the tree
        total_sum = self.calculate_total_sum(root)

        # Step 2: Initialize a variable to keep track of the maximum product
        self.max_product = 0

        # Step 3: Traverse the tree again to calculate the product for each subtree
        self.calculate_max_product(root, total_sum)

        # Step 4: Return the maximum product modulo 10^9 + 7
        return self.max_product % (10**9 + 7)