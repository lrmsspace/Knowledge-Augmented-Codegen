# Source: https://leetcode.com/problems/cousins-in-binary-tree/   |   Difficulty: Easy
#
# Problem Description:
# Given the root of a binary tree with unique values and the values of two different nodes of the tree x and y, return true if the nodes corresponding to the values x and y in the tree are cousins, or false otherwise.
#
# Two nodes of a binary tree are cousins if they have the same depth with different parents.
#
# Note that in a binary tree, the root node is at the depth 0, and children of each depth k node are at the depth k + 1.
#
# Example:
# Input: root = [1,2,3,4], x = 4, y = 3
# Output: false
#
# Constraints:
# The number of nodes in the tree is in the range [2, 100].
# 	1 <= Node.val <= 100
# 	Each node has a unique value.
# 	x != y
# 	x and y are exist in the tree.
#
# Helpful references (internal KB):
# - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
#   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
#   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
#   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
#   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
#   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
# - Lowest Common Ancestor (tree, array, dfs)
#   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
#   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
#   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
#   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
#   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
# - Depth First Search (graph, dfs)
#   • When to use: Use DFS to explore all reachable vertices from a source, find connected components, or detect cycles in a graph. It is suitable for problems requiring deep exploration before backtracking.
#   • Idea: Depth First Search systematically explores a graph by going as deep as possible along each branch before backtracking. It visits each vertex and edge at most once, resulting in an O(V + E) time complexity.
#   • Invariants: Before visiting a node 'u', it is marked as unvisited.; After visiting a node 'u', it is marked as visited, and all its reachable neighbors have been explored.
#   • Tips: Use a 'visited' set or array to prevent infinite loops in cyclic graphs.; Recursion is common, but an explicit stack can manage deep graphs or avoid recursion limits.
#   • Pitfalls: Can lead to stack overflow errors on very deep graphs if implemented recursively.; Does not guarantee shortest paths in general unweighted graphs (BFS does).
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
    def isCousins(self, root, x, y):
        """
        :type root: Optional[TreeNode]
        :type x: int
        :type y: int
        :rtype: bool
        """
        from collections import deque

        if not root:
            return False

        queue = deque([(root, None)])  # (node, parent)

        while queue:
            level_size = len(queue)
            x_parent = None
            y_parent = None

            for _ in range(level_size):
                node, parent = queue.popleft()

                if node.val == x:
                    x_parent = parent
                if node.val == y:
                    y_parent = parent

                if node.left:
                    queue.append((node.left, node))
                if node.right:
                    queue.append((node.right, node))

            if x_parent and y_parent:
                return x_parent != y_parent  # Same level but different parents
            if x_parent or y_parent:
                return False  # Found one but not the other

        return False