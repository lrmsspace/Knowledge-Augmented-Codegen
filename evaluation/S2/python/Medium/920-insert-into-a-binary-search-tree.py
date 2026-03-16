# Source: https://leetcode.com/problems/insert-into-a-binary-search-tree/   |   Difficulty: Medium
#
# Problem Description:
# You are given the root node of a binary search tree (BST) and a value to insert into the tree. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.
#
# Notice that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.
#
# Example:
# Input: root = [4,2,7,1,3], val = 5
# Output: [4,2,7,1,3,5]
# Explanation: Another accepted tree is:
#
# Constraints:
# The number of nodes in the tree will be in the range [0, 104].
# 	-108 <= Node.val <= 108
# 	All the values Node.val are unique.
# 	-108 <= val <= 108
# 	It's guaranteed that val does not exist in the original BST.
#
# Helpful references (internal KB):
# - Binary Search Trees
#  (tree, recursion)
#   • When to use: When you need to store ordered data that allows efficient searching, insertion, and deletion while maintaining sorted order. It's suitable for dynamic datasets where elements frequently change.
#   • Idea: A Binary Search Tree (BST) is a node-based binary tree where keys in the left subtree are smaller than the node's key, and keys in the right subtree are larger. Operations like search, insert, and delete typically run in O(log N) average time and O(N) worst-case.
#   • Invariants: For any node, all keys in its left subtree are strictly less than its key.; For any node, all keys in its right subtree are strictly greater than its key.
#   • Tips: Maintain the BST property: left child < parent < right child.; Recursion simplifies many operations like search, insert, and traversal.
#   • Pitfalls: Unbalanced trees can degrade performance to O(N) for all operations.; Incorrect handling of duplicate keys can break BST properties or lead to data loss.
# - Randomized Heap (heap, tree, randomized, recursion)
#   • When to use: Use when needing a heap with efficient merge operations and guaranteed expected logarithmic time for all standard operations, including arbitrary element removal.
#   • Idea: A randomized heap is a binary tree-based heap that uses randomization to maintain heap properties, ensuring all operations like insertion, deletion, and merging run in expected O(log n) time.
#   • Invariants: The root node always contains the minimum (or maximum) element.; Every node's value is less than or equal to (or greater than or equal to) its children's values.
#   • Tips: Randomization simplifies implementation compared to other mergeable heaps.; Expected time complexity is generally sufficient for practical purposes.
#   • Pitfalls: Worst-case time complexity can be higher, though rare.; Relies on a good random number generator.
# - MEX (minimal excluded) of a sequence (tree, binary-search)
#   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
#   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
#   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
#   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
#   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
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
    def insertIntoBST(self, root, val):
        """
        :type root: Optional[TreeNode]
        :type val: int
        :rtype: Optional[TreeNode]
        """
        if not root:
            return TreeNode(val)

        if val < root.val:
            root.left = self.insertIntoBST(root.left, val)
        else:
            root.right = self.insertIntoBST(root.right, val)

        return root