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
# - Depth First Search (tree, graph, dfs)
#   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
#   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
#   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
#   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
#   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
# - Balanced Search Trees (tree, ds, binary-search, recursion)
#   • When to use: When you need to store a dynamic set of ordered data and require guaranteed logarithmic time complexity for search, insertion, and deletion operations, even in worst-case scenarios.
#   • Idea: Balanced search trees are a class of self-balancing binary search trees that maintain a logarithmic height to ensure O(log N) time complexity for core operations like search, insertion, and deletion. They achieve this balance through structural modifications such as rotations or node splitting/merging.
#   • Invariants: For any node, all keys in its left subtree are less than its key(s), and all keys in its right subtree are greater than its key(s).; The height of the tree is always proportional to log N, ensuring O(log N) operations.
#   • Tips: Understand the specific balancing rules (e.g., AVL rotations, Red-Black tree color properties, 2-3 tree node splits).; Consider the trade-offs between different balanced tree types (e.g., simpler implementation vs. stricter balance).
#   • Pitfalls: Implementation complexity can be high due to intricate rebalancing logic.; Overhead for rebalancing operations might be noticeable for very small N.
# - Breadth-first search (graph, queue, array, bfs)
#   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
#   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
#   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
#   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
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
        self.cumulative_sum = 0

        def reverse_inorder_traversal(node):
            if not node:
                return

            # Traverse the right subtree first
            reverse_inorder_traversal(node.right)

            # Update the cumulative sum and the current node's value
            self.cumulative_sum += node.val
            node.val = self.cumulative_sum

            # Traverse the left subtree
            reverse_inorder_traversal(node.left)

        reverse_inorder_traversal(root)
        return root