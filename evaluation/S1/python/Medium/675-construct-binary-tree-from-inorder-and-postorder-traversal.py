# Source: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/   |   Difficulty: Medium
#
# Problem Description:
# Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.
#
# Example:
# Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
# Output: [3,9,20,null,null,15,7]
#
# Constraints:
# 1 <= inorder.length <= 3000
# 	postorder.length == inorder.length
# 	-3000 <= inorder[i], postorder[i] <= 3000
# 	inorder and postorder consist of unique values.
# 	Each value of postorder also appears in inorder.
# 	inorder is guaranteed to be the inorder traversal of the tree.
# 	postorder is guaranteed to be the postorder traversal of the tree.
#
# Helpful references (internal KB):
# - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
#   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
#   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
#   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
#   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
#   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
# - Ordered Set - Python (ds, hashing)
#   • When to use: When you need a collection of unique items where the order of insertion must be preserved, allowing for efficient membership testing and iteration in that specific order.
#   • Idea: An ordered set stores unique elements while maintaining their original insertion order. It provides O(1) average time complexity for additions, deletions, and membership checks, typically implemented using a hash table combined with a linked list.
#   • Invariants: Every element within the set is unique.; The sequence of elements during iteration strictly follows their initial insertion order.
#   • Tips: In Python 3.7+, standard `dict`s maintain insertion order, effectively serving as ordered sets.; Use `collections.OrderedDict` for older Python versions or explicit semantic clarity.
#   • Pitfalls: Order is based on insertion, not value-based sorting; do not confuse the two.; Modifying an element's hash value while it's in the set can lead to undefined behavior.
# - Binary Search Trees
#  (tree, recursion)
#   • When to use: When you need to store ordered data that allows efficient searching, insertion, and deletion while maintaining sorted order. It's suitable for dynamic datasets where elements frequently change.
#   • Idea: A Binary Search Tree (BST) is a node-based binary tree where keys in the left subtree are smaller than the node's key, and keys in the right subtree are larger. Operations like search, insert, and delete typically run in O(log N) average time and O(N) worst-case.
#   • Invariants: For any node, all keys in its left subtree are strictly less than its key.; For any node, all keys in its right subtree are strictly greater than its key.
#   • Tips: Maintain the BST property: left child < parent < right child.; Recursion simplifies many operations like search, insert, and traversal.
#   • Pitfalls: Unbalanced trees can degrade performance to O(N) for all operations.; Incorrect handling of duplicate keys can break BST properties or lead to data loss.
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
    def buildTree(self, inorder, postorder):
        """
        :type inorder: List[int]
        :type postorder: List[int]
        :rtype: Optional[TreeNode]
        """
        if not inorder or not postorder:
            return None

        # The last element in postorder is the root
        root_val = postorder.pop()
        root = TreeNode(root_val)

        # Find the index of the root in inorder
        inorder_index = inorder.index(root_val)

        # Recursively build the right and left subtrees
        # Note: We build the right subtree first because we are popping from the end of postorder
        root.right = self.buildTree(inorder[inorder_index + 1:], postorder)
        root.left = self.buildTree(inorder[:inorder_index], postorder)

        return root