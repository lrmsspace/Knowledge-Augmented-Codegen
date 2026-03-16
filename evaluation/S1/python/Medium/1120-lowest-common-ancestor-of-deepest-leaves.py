# Source: https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, return the lowest common ancestor of its deepest leaves.
#
# Recall that:
#
#
# 	The node of a binary tree is a leaf if and only if it has no children
# 	The depth of the root of the tree is 0. if the depth of a node is d, the depth of each of its children is d + 1.
# 	The lowest common ancestor of a set S of nodes, is the node A with the largest depth such that every node in S is in the subtree with root A.
#
# Example:
# Input: root = [3,5,1,6,2,0,8,null,null,7,4]
# Output: [2,7,4]
# Explanation: We return the node with value 2, colored in yellow in the diagram.
# The nodes coloured in blue are the deepest leaf-nodes of the tree.
# Note that nodes 6, 0, and 8 are also leaf nodes, but the depth of them is 2, but the depth of nodes 7 and 4 is 3.
#
# Constraints:
# The number of nodes in the tree will be in the range [1, 1000].
# 	0 <= Node.val <= 1000
# 	The values of the nodes in the tree are unique.
#
#
#  
# Note: This question is the same as 865: https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/
#
# Helpful references (internal KB):
# - Lowest Common Ancestor (tree, array, dfs)
#   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
#   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
#   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
#   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
#   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
# - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
#   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
#   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
#   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
#   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
#   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
# - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
#   • When to use: Use this algorithm when you need to find the lowest common ancestor for multiple pairs of nodes in a tree, and all queries are available before processing begins.
#   • Idea: Tarjan's off-line algorithm efficiently computes the Lowest Common Ancestor (LCA) for all given query pairs in a tree. It leverages a Depth First Search (DFS) traversal combined with a Union-Find data structure to achieve an optimal O(N + M) time complexity.
#   • Invariants: When DFS returns from a node u, all nodes in the subtree rooted at u have been visited and their components merged into u's representative.; For any node v, find(v) in the Union-Find structure returns the representative of the component containing v and its fully processed descendants.
#   • Tips: Process queries associated with a node during its DFS post-order traversal.; Use Union-Find to keep track of visited nodes and their ancestors.
#   • Pitfalls: Forgetting to mark nodes as visited after processing their subtree.; Incorrectly handling the Union-Find union or find operations.
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
    def lcaDeepestLeaves(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: Optional[TreeNode]
        """
        def dfs(node):
            if not node:
                return (None, 0)
            
            left_lca, left_depth = dfs(node.left)
            right_lca, right_depth = dfs(node.right)
            
            if left_depth > right_depth:
                return (left_lca, left_depth + 1)
            elif right_depth > left_depth:
                return (right_lca, right_depth + 1)
            else:
                return (node, left_depth + 1)
        
        lca, _ = dfs(root)
        return lca