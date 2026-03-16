# Source: https://leetcode.com/problems/insufficient-nodes-in-root-to-leaf-paths/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree and an integer limit, delete all insufficient nodes in the tree simultaneously, and return the root of the resulting binary tree.
#
# A node is insufficient if every root to leaf path intersecting this node has a sum strictly less than limit.
#
# A leaf is a node with no children.
#
# Example:
# Input: root = [1,2,3,4,-99,-99,7,8,9,-99,-99,12,13,-99,14], limit = 1
# Output: [1,2,3,4,null,null,7,8,9,null,14]
#
# Constraints:
# The number of nodes in the tree is in the range [1, 5000].
# 	-105 <= Node.val <= 105
# 	-109 <= limit <= 109
#
# Helpful references (internal KB):
# - Deleting from a data structure in_log_n (ds, segment-tree, dfs, recursion)
#   • When to use: Use when processing a sequence of additions, deletions, and queries offline, where elements have specific time intervals of existence. It efficiently handles dynamic data structure operations by leveraging a segment tree over time.
#   • Idea: This technique uses a segment tree over the timeline of queries to manage elements with varying lifespans. Queries are processed offline via DFS, adding elements upon entering a node and undoing additions upon exiting, achieving O(T(n) log n) deletion complexity.
#   • Invariants: When entering a segment tree node, all elements associated with that node's time range are added to the active data structure.; When exiting a segment tree node, all elements added upon entry are removed, restoring the data structure to its state before entering.
#   • Tips: Ensure the base data structure supports efficient addition and undo operations.; Carefully manage element additions and removals during DFS traversal.
#   • Pitfalls: Forgetting to undo changes when backtracking from a segment tree node.; Incorrectly mapping element lifespans to segment tree nodes.
# - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
#   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
#   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
#   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
#   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
#   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
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
    def sufficientSubset(self, root, limit):
        """
        :type root: Optional[TreeNode]
        :type limit: int
        :rtype: Optional[TreeNode]
        """
        def dfs(node, path_sum):
            if not node:
                return None
            
            path_sum += node.val
            
            if not node.left and not node.right:  # Leaf node
                return node if path_sum >= limit else None
            
            node.left = dfs(node.left, path_sum)
            node.right = dfs(node.right, path_sum)
            
            return node if node.left or node.right else None
        
        return dfs(root, 0)