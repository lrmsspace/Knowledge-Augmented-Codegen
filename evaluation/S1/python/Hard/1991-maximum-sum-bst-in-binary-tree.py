# Source: https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/   |   Difficulty: Hard
#
# Problem Description:
# Given a binary tree root, return the maximum sum of all keys of any sub-tree which is also a Binary Search Tree (BST).
#
# Assume a BST is defined as follows:
#
#
# 	The left subtree of a node contains only nodes with keys less than the node's key.
# 	The right subtree of a node contains only nodes with keys greater than the node's key.
# 	Both the left and right subtrees must also be binary search trees.
#
# Example:
# Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
# Output: 20
# Explanation: Maximum sum in a valid Binary search tree is obtained in root node with key equal to 3.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 4 * 104].
# 	-4 * 104 <= Node.val <= 4 * 104
#
# Helpful references (internal KB):
# - Depth First Search (tree, graph, dfs)
#   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
#   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
#   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
#   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
#   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Balanced Search Trees (tree, ds, binary-search, recursion)
#   • When to use: When you need to store a dynamic set of ordered data and require guaranteed logarithmic time complexity for search, insertion, and deletion operations, even in worst-case scenarios.
#   • Idea: Balanced search trees are a class of self-balancing binary search trees that maintain a logarithmic height to ensure O(log N) time complexity for core operations like search, insertion, and deletion. They achieve this balance through structural modifications such as rotations or node splitting/merging.
#   • Invariants: For any node, all keys in its left subtree are less than its key(s), and all keys in its right subtree are greater than its key(s).; The height of the tree is always proportional to log N, ensuring O(log N) operations.
#   • Tips: Understand the specific balancing rules (e.g., AVL rotations, Red-Black tree color properties, 2-3 tree node splits).; Consider the trade-offs between different balanced tree types (e.g., simpler implementation vs. stricter balance).
#   • Pitfalls: Implementation complexity can be high due to intricate rebalancing logic.; Overhead for rebalancing operations might be noticeable for very small N.
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
    def maxSumBST(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        self.max_sum = 0
        
        def post_order(node):
            if not node:
                return (True, 0, float('inf'), float('-inf'))  # is_bst, sum, min_val, max_val
            
            left_is_bst, left_sum, left_min, left_max = post_order(node.left)
            right_is_bst, right_sum, right_min, right_max = post_order(node.right)
            
            if left_is_bst and right_is_bst and left_max < node.val < right_min:
                current_sum = left_sum + right_sum + node.val
                self.max_sum = max(self.max_sum, current_sum)
                return (True, current_sum, min(left_min, node.val), max(right_max, node.val))
            else:
                return (False, 0, 0, 0)
        
        post_order(root)
        return self.max_sum