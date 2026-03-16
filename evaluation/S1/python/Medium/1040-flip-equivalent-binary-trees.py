# Source: https://leetcode.com/problems/flip-equivalent-binary-trees/   |   Difficulty: Medium
#
# Problem Description:
# For a binary tree T, we can define a flip operation as follows: choose any node, and swap the left and right child subtrees.
#
# A binary tree X is flip equivalent to a binary tree Y if and only if we can make X equal to Y after some number of flip operations.
#
# Given the roots of two binary trees root1 and root2, return true if the two trees are flip equivalent or false otherwise.
#
# Example:
# Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
# Output: true
# Explanation: We flipped at nodes with values 1, 3, and 5.
#
# Constraints:
# The number of nodes in each tree is in the range [0, 100].
# 	Each tree will have unique node values in the range [0, 99].
#
# Helpful references (internal KB):
# - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
#   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
#   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
#   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
#   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
#   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
# - Checking a graph for acyclicity and finding a cycle in O(M) (graph, array, dfs)
#   • When to use: Use when needing to determine if a graph contains any cycles or to identify one such cycle. It is applicable to both directed and undirected graphs.
#   • Idea: This algorithm uses Depth First Search to detect cycles in a graph by tracking visited states of nodes during traversal. It runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
#   • Invariants: All nodes currently on the DFS recursion stack are marked as 'gray' (or equivalent).; All nodes fully explored and not part of the current path are marked as 'black' (or equivalent).
#   • Tips: For directed graphs, use a three-color scheme (white, gray, black) to distinguish states.; For undirected graphs, a simple visited array and checking against the immediate parent is sufficient.
#   • Pitfalls: Incorrectly handling the parent edge in undirected graphs can lead to false cycle detections.; Failing to distinguish between nodes currently in the recursion stack (gray) and fully processed nodes (black) in directed graphs.
# - Balanced Search Trees (tree, ds, recursion)
#   • When to use: When needing a self-balancing search tree that guarantees logarithmic time complexity for search and insertion operations. Useful for maintaining data in sorted order with consistent performance, especially when frequent updates are expected.
#   • Idea: A 2-3 tree is a self-balancing search tree where every node has either two children (a 2-node) or three children (a 3-node), ensuring all leaves are at the same depth. It guarantees O(log N) time complexity for search, insertion, and deletion operations.
#   • Invariants: All leaves are at the same depth from the root.; Every node is either a 2-node (one key, two children) or a 3-node (two keys, three children).
#   • Tips: Understand the two node types: 2-nodes (one key, two children) and 3-nodes (two keys, three children).; Insertion always starts by finding the leaf position, then propagates splits upwards if a 4-node is formed.
#   • Pitfalls: Incorrectly handling the promotion of keys during node splits can break the tree's structure.; Forgetting to update parent links after a node split or merge operation.
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
    def flipEquiv(self, root1, root2):
        """
        :type root1: Optional[TreeNode]
        :type root2: Optional[TreeNode]
        :rtype: bool
        """
        if not root1 and not root2:
            return True
        if not root1 or not root2 or root1.val != root2.val:
            return False

        return (self.flipEquiv(root1.left, root2.left) and self.flipEquiv(root1.right, root2.right)) or \
               (self.flipEquiv(root1.left, root2.right) and self.flipEquiv(root1.right, root2.left))