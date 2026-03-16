# Source: https://leetcode.com/problems/add-one-row-to-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree and two integers val and depth, add a row of nodes with value val at the given depth depth.
#
# Note that the root node is at depth 1.
#
# The adding rule is:
#
#
# 	Given the integer depth, for each not null tree node cur at the depth depth - 1, create two tree nodes with value val as cur's left subtree root and right subtree root.
# 	cur's original left subtree should be the left subtree of the new left subtree root.
# 	cur's original right subtree should be the right subtree of the new right subtree root.
# 	If depth == 1 that means there is no depth depth - 1 at all, then create a tree node with value val as the new root of the whole original tree, and the original tree is the new root's left subtree.
#
# Example:
# Input: root = [4,2,6,3,1,5], val = 1, depth = 2
# Output: [4,1,1,2,null,null,6,3,1,5]
#
# Constraints:
# The number of nodes in the tree is in the range [1, 104].
# 	The depth of the tree is in the range [1, 104].
# 	-100 <= Node.val <= 100
# 	-105 <= val <= 105
# 	1 <= depth <= the depth of tree + 1
#
# Helpful references (internal KB):
# - Linked-list implementations of collections (linked-list, stack, simulation)
#   • When to use: Use when a Last-In, First-Out (LIFO) data structure is required, and dynamic size with efficient O(1) push and pop operations is crucial, especially without a fixed capacity.
#   • Idea: This describes implementing a stack using a singly linked list, where elements are added and removed from the head of the list. Both push and pop operations achieve O(1) time complexity.
#   • Invariants: The 'first' pointer always points to the top element of the stack, or is null if the stack is empty.; Each node's 'next' pointer correctly links to the subsequent element in the stack, maintaining the LIFO order.
#   • Tips: Maintain a 'first' pointer to the head of the linked list, representing the stack's top.; Push operation involves creating a new node, linking it to the current 'first', then updating 'first'.
#   • Pitfalls: Forgetting to handle the empty stack case for pop, leading to `NoSuchElementException`.; Incorrectly updating the 'first' pointer during push or pop, which can break the list structure.
# - Prüfer code (tree, heap, simulation, greedy)
#   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
#   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
#   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
#   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
#   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
# - Sqrt Tree (array, tree, recursion, simulation)
#   • When to use: Use for efficient range queries on an array, achieving very low query complexity by leveraging a hierarchical block decomposition and specific structural properties like power-of-two block sizes.
#   • Idea: A Sqrt Tree is a hierarchical data structure designed for answering range queries on an array, achieving O(log log n) or better query time by recursively decomposing the array into blocks and layers.
#   • Invariants: Each layer of the Sqrt Tree consists of segments of equal length.; All blocks within a given layer have an equal, power-of-two size.
#   • Tips: Pad the input array with dummy elements to ensure its size is a power of two for simplified block calculations.; Ensure all block sizes on each layer are powers of two to enable efficient binary representation tricks for queries.
#   • Pitfalls: Incorrectly calculating block boundaries or segment sizes, leading to off-by-one errors or out-of-bounds access.; Overlooking the memory overhead associated with storing precomputed values for all blocks across multiple layers.
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
    def addOneRow(self, root, val, depth):
        """
        :type root: Optional[TreeNode]
        :type val: int
        :type depth: int
        :rtype: Optional[TreeNode]
        """
        if depth == 1:
            new_root = TreeNode(val)
            new_root.left = root
            return new_root
        
        def dfs(node, current_depth):
            if not node:
                return
            
            if current_depth == depth - 1:
                old_left = node.left
                old_right = node.right
                
                node.left = TreeNode(val)
                node.left.left = old_left
                
                node.right = TreeNode(val)
                node.right.right = old_right
            else:
                dfs(node.left, current_depth + 1)
                dfs(node.right, current_depth + 1)
        
        dfs(root, 1)
        return root