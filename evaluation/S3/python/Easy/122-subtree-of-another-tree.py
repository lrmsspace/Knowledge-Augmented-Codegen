# Source: https://leetcode.com/problems/subtree-of-another-tree/   |   Difficulty: Easy
#
# Problem Description:
# Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.
#
# A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.
#
# Example:
# Input: root = [3,4,5,1,2], subRoot = [4,1,2]
# Output: true
#
# Constraints:
# The number of nodes in the root tree is in the range [1, 2000].
# 	The number of nodes in the subRoot tree is in the range [1, 1000].
# 	-104 <= root.val <= 104
# 	-104 <= subRoot.val <= 104
#
# Helpful references (internal KB):
# - Lowest Common Ancestor (tree, array, dfs)
#   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
#   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
#   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
#   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
#   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
# - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
#   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
#   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
#   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
#   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
#   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
# - Lowest Common Ancestor - Farach-Colton and Bender Algorithm (tree, array, dfs)
#   • When to use: When frequent LCA queries are needed on a static tree, and optimal query time is critical. It's suitable for scenarios requiring O(1) query time after initial preprocessing.
#   • Idea: This algorithm finds the Lowest Common Ancestor (LCA) of two nodes in a tree by reducing the problem to Range Minimum Query (RMQ) on an Euler tour. It preprocesses the tree in O(N) time using DFS to build an array of nodes and their depths, then answers LCA queries in O(1) time.
#   • Invariants: The Euler tour array contains every edge traversed twice, and each node appears at least once.; The depth array stores the correct distance from the root for each node's occurrence in the Euler tour.
#   • Tips: Perform a DFS to construct the Euler tour and depth array.; Store both the node identifier and its depth during the Euler tour.
#   • Pitfalls: Incorrectly defining the start and end indices for the RMQ on the Euler tour.; Off-by-one errors when mapping Euler tour indices to original nodes or depths.
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
    def isSubtree(self, root, subRoot):
        """
        :type root: Optional[TreeNode]
        :type subRoot: Optional[TreeNode]
        :rtype: bool
        """
        if not root:
            return False
        if self.isSameTree(root, subRoot):
            return True
        return self.isSubtree(root.left, subRoot) or self.isSubtree(root.right, subRoot)