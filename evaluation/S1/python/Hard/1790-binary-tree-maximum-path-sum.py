# Source: https://leetcode.com/problems/binary-tree-maximum-path-sum/   |   Difficulty: Hard
#
# Problem Description:
# A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.
#
# The path sum of a path is the sum of the node's values in the path.
#
# Given the root of a binary tree, return the maximum path sum of any non-empty path.
#
# Example:
# Input: root = [1,2,3]
# Output: 6
# Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 3 * 104].
# 	-1000 <= Node.val <= 1000
#
# Helpful references (internal KB):
# - Depth First Search (tree, graph, dfs)
#   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
#   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
#   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
#   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
#   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Kuhn's Algorithm for Maximum Bipartite Matching (graph, array, greedy, dfs)
#   • When to use: Use when finding a maximum matching in a bipartite graph, particularly when performance on random graphs can be improved by heuristic pre-matching.
#   • Idea: This algorithm finds a maximum matching in a bipartite graph by iteratively searching for augmenting paths using Depth-First Search. An improved version incorporates greedy heuristics to find an initial matching, potentially speeding up practical runtime while maintaining the O(V*E) worst-case complexity.
#   • Invariants: After each successful DFS call, the size of the current matching increases by one.; The 'mt' array correctly stores the current matching pairs for all vertices.
#   • Tips: Pre-calculate an initial matching using a simple heuristic to reduce DFS calls.; Consider heuristics like iterating over vertices or selecting from smallest degree vertices first.
#   • Pitfalls: Forgetting to reset the 'visited' array for each new DFS search in the main loop.; Incorrectly modifying the main loop logic when integrating heuristic pre-matching.
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
    def maxPathSum(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        self.max_sum = float('-inf')

        def dfs(node):
            if not node:
                return 0

            left_gain = max(dfs(node.left), 0)  # Only consider positive gains
            right_gain = max(dfs(node.right), 0)

            # Price to start a new path where `node` is the highest node
            price_newpath = node.val + left_gain + right_gain

            # Update max_sum if it's better to start a new path
            self.max_sum = max(self.max_sum, price_newpath)

            # For recursion: return the max gain if continue the same path
            return node.val + max(left_gain, right_gain)

        dfs(root)
        return self.max_sum