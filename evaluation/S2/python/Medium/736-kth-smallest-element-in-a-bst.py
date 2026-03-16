# Source: https://leetcode.com/problems/kth-smallest-element-in-a-bst/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) of all the values of the nodes in the tree.
#
# Example:
# Input: root = [3,1,4,null,2], k = 1
# Output: 1
#
# Constraints:
# The number of nodes in the tree is n.
# 	1 <= k <= n <= 104
# 	0 <= Node.val <= 104
#
#
#  
# Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize?
#
# Helpful references (internal KB):
# - Binary Search Trees
#  (tree, quickselect)
#   • When to use: Use when maintaining an ordered collection of elements that requires efficient search, insertion, and deletion operations. It is also suitable for finding minimum, maximum, floor, and ceiling values.
#   • Idea: A Binary Search Tree (BST) is a node-based binary tree where keys in the left subtree are smaller than the node's key, and keys in the right subtree are larger. Core operations like search, insert, and delete typically run in O(h) time, where h is the tree's height.
#   • Invariants: For any node, all keys in its left subtree are less than its own key.; For any node, all keys in its right subtree are greater than its own key.
#   • Tips: Maintain subtree sizes for order-statistic operations like finding the k-th smallest element.; Consider self-balancing variants (AVL, Red-Black) to guarantee O(log N) worst-case performance.
#   • Pitfalls: Unbalanced trees can degrade to O(N) performance for all operations.; Forgetting to update parent pointers or subtree sizes during modifications.
# - kth-largest-element-in-an-array (array, merge-sort)
#   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
#   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
#   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
#   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
#   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
# - Prüfer code (tree, heap, simulation, greedy)
#   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
#   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
#   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
#   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
#   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
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
    def kthSmallest(self, root, k):
        """
        :type root: Optional[TreeNode]
        :type k: int
        :rtype: int
        """
        # Approach 1: In-order Traversal (O(N) time, O(H) space)
        # def in_order_traversal(node):
        #     if not node:
        #         return []
        #     return in_order_traversal(node.left) + [node.val] + in_order_traversal(node.right)

        # sorted_values = in_order_traversal(root)
        # return sorted_values[k - 1]

        # Approach 2: Iterative In-order Traversal (O(N) time, O(H) space)
        stack = []
        current = root
        count = 0

        while stack or current:
            while current:
                stack.append(current)
                current = current.left

            current = stack.pop()
            count += 1
            if count == k:
                return current.val
            current = current.right