# Source: https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
#
# As a reminder, a binary search tree is a tree that satisfies these constraints:
#
#
# 	The left subtree of a node contains only nodes with keys less than the node's key.
# 	The right subtree of a node contains only nodes with keys greater than the node's key.
# 	Both the left and right subtrees must also be binary search trees.
#
# Example:
# Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
# Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
#
# Constraints:
# The number of nodes in the tree is in the range [1, 100].
# 	0 <= Node.val <= 100
# 	All the values in the tree are unique.
#
#
#  
# Note: This question is the same as 538: https://leetcode.com/problems/convert-bst-to-greater-tree/
#
# Helpful references (internal KB):
# - Binary Search Trees
#  (tree, recursion)
#   • When to use: When you need to store ordered data that allows efficient searching, insertion, and deletion while maintaining sorted order. It's suitable for dynamic datasets where elements frequently change.
#   • Idea: A Binary Search Tree (BST) is a node-based binary tree where keys in the left subtree are smaller than the node's key, and keys in the right subtree are larger. Operations like search, insert, and delete typically run in O(log N) average time and O(N) worst-case.
#   • Invariants: For any node, all keys in its left subtree are strictly less than its key.; For any node, all keys in its right subtree are strictly greater than its key.
#   • Tips: Maintain the BST property: left child < parent < right child.; Recursion simplifies many operations like search, insert, and traversal.
#   • Pitfalls: Unbalanced trees can degrade performance to O(N) for all operations.; Incorrect handling of duplicate keys can break BST properties or lead to data loss.
# - Binary Search Trees
#  (tree, enumeration)
#   • When to use: Use when you need to store ordered data in a hierarchical structure that allows for efficient searching, insertion, and deletion operations. It is suitable for dynamic datasets where elements frequently change while maintaining sorted order.
#   • Idea: A Binary Search Tree (BST) is a node-based binary tree data structure where each node has a key, and all keys in the left subtree are less than the node's key, while all keys in the right subtree are greater. Basic operations like search, insertion, and deletion typically have an average time complexity of O(log N) but can degrade to O(N) in the worst case.
#   • Invariants: For every node N, if L is in N's left subtree, then L.key < N.key.; For every node N, if R is in N's right subtree, then R.key > N.key.
#   • Tips: Understand the recursive definition for traversal and operations.; Handle edge cases like empty tree, single node, or leaf nodes carefully.
#   • Pitfalls: Unbalanced trees can lead to O(N) worst-case performance for all operations.; Incorrect handling of duplicate keys can lead to data loss or incorrect structure.
# - Treap (Cartesian tree) (tree, recursion, binary-search)
#   • When to use: When you need a self-balancing binary search tree that supports efficient split and merge operations, often used for dynamic set management or range queries on mutable data.
#   • Idea: A Treap is a randomized binary search tree that maintains both BST properties on keys and heap properties on priorities (randomly assigned). It supports efficient operations like split and merge, typically with an average time complexity of O(log N).
#   • Invariants: For any node, its key is greater than or equal to all keys in its left subtree.; For any node, its key is less than all keys in its right subtree.
#   • Tips: Understand the recursive nature of Split and Merge operations.; Randomly assign priorities (Y values) to ensure probabilistic balancing.
#   • Pitfalls: Incorrect handling of null pointers or empty subtrees in recursion.; Forgetting to update parent pointers or root pointers after operations.
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
    def bstToGst(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: Optional[TreeNode]
        """
        self.sum = 0
        
        def reverse_inorder(node):
            if not node:
                return
            
            # Traverse the right subtree first
            reverse_inorder(node.right)
            
            # Update the current node's value
            self.sum += node.val
            node.val = self.sum
            
            # Traverse the left subtree
            reverse_inorder(node.left)
        
        reverse_inorder(root)
        return root