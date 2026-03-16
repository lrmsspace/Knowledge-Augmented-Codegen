# Source: https://leetcode.com/problems/all-elements-in-two-binary-search-trees/   |   Difficulty: Medium
#
# Problem Description:
# Given two binary search trees root1 and root2, return a list containing all the integers from both trees sorted in ascending order.
#
# Example:
# Input: root1 = [2,1,4], root2 = [1,0,3]
# Output: [0,1,1,2,3,4]
#
# Constraints:
# The number of nodes in each tree is in the range [0, 5000].
# 	-105 <= Node.val <= 105
#
# Helpful references (internal KB):
# - Lowest Common Ancestor (tree, array, dfs)
#   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
#   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
#   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
#   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
#   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
# - Deleting from a data structure in_log_n (ds, segment-tree, dfs, recursion)
#   • When to use: Use when processing a sequence of additions, deletions, and queries offline, where elements have specific time intervals of existence. It efficiently handles dynamic data structure operations by leveraging a segment tree over time.
#   • Idea: This technique uses a segment tree over the timeline of queries to manage elements with varying lifespans. Queries are processed offline via DFS, adding elements upon entering a node and undoing additions upon exiting, achieving O(T(n) log n) deletion complexity.
#   • Invariants: When entering a segment tree node, all elements associated with that node's time range are added to the active data structure.; When exiting a segment tree node, all elements added upon entry are removed, restoring the data structure to its state before entering.
#   • Tips: Ensure the base data structure supports efficient addition and undo operations.; Carefully manage element additions and removals during DFS traversal.
#   • Pitfalls: Forgetting to undo changes when backtracking from a segment tree node.; Incorrectly mapping element lifespans to segment tree nodes.
# - Lowest Common Ancestor (array, min-window)
#   • When to use: Use when needing to find the lowest common ancestor of two nodes in a tree efficiently for multiple queries. This approach is ideal when the tree is static and preprocessing is acceptable.
#   • Idea: This method finds the LCA by converting the problem into a Range Minimum Query on an Euler tour of the tree's depths. It preprocesses the tree in O(N log N) or O(N) time and answers queries in O(log N) or O(1) time.
#   • Invariants: The Euler tour array correctly records nodes in DFS entry/exit order.; The depth array stores the correct depth for each node in the Euler tour.
#   • Tips: Perform a DFS to construct the Euler tour and depth array.; Store the first occurrence index of each node in the Euler tour.
#   • Pitfalls: Incorrectly constructing the Euler tour or depth array.; Off-by-one errors when mapping Euler tour indices to original nodes.
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
    def getAllElements(self, root1, root2):
        """
        :type root1: Optional[TreeNode]
        :type root2: Optional[TreeNode]
        :rtype: List[int]
        """
        def inorder_traversal(root, result):
            if root:
                inorder_traversal(root.left, result)
                result.append(root.val)
                inorder_traversal(root.right, result)

        result = []
        inorder_traversal(root1, result)
        inorder_traversal(root2, result)
        return sorted(result)