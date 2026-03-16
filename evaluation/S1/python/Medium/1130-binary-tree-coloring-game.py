# Source: https://leetcode.com/problems/binary-tree-coloring-game/   |   Difficulty: Medium
#
# Problem Description:
# Two players play a turn based game on a binary tree. We are given the root of this binary tree, and the number of nodes n in the tree. n is odd, and each node has a distinct value from 1 to n.
#
# Initially, the first player names a value x with 1 <= x <= n, and the second player names a value y with 1 <= y <= n and y != x. The first player colors the node with value x red, and the second player colors the node with value y blue.
#
# Then, the players take turns starting with the first player. In each turn, that player chooses a node of their color (red if player 1, blue if player 2) and colors an uncolored neighbor of the chosen node (either the left child, right child, or parent of the chosen node.)
#
# If (and only if) a player cannot choose such a node in this way, they must pass their turn. If both players pass their turn, the game ends, and the winner is the player that colored more nodes.
#
# You are the second player. If it is possible to choose such a y to ensure you win the game, return true. If it is not possible, return false.
#
# Example:
# Input: root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
# Output: true
# Explanation: The second player can choose the node with value 2.
#
# Constraints:
# The number of nodes in the tree is n.
# 	1 <= x <= n <= 100
# 	n is odd.
# 	1 <= Node.val <= n
# 	All the values of the tree are unique.
#
# Helpful references (internal KB):
# - Depth First Search (tree, graph, dfs)
#   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
#   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
#   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
#   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
#   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
# - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
#   • When to use: Use when you need to answer multiple Lowest Common Ancestor (LCA) queries on a static tree, and all queries are available before processing.
#   • Idea: Tarjan's off-line LCA algorithm efficiently computes the Lowest Common Ancestor for multiple pairs of nodes in a tree using a single Depth-First Search traversal combined with a Disjoint Set Union data structure, achieving nearly linear time complexity.
#   • Invariants: When DFS is at node `v`, all its children's subtrees have been fully processed and merged into `v`'s DSU set.; For any node `x` whose DFS has completed, `ancestor[find_set(x)]` stores an ancestor of `x` on the path to the root.
#   • Tips: Initialize each node as its own set in DSU with itself as the ancestor.; Process queries for a node only after its children's subtrees are fully processed.
#   • Pitfalls: Not suitable for online LCA queries or dynamic tree structures.; Incorrectly updating the `ancestor` array in the DSU can lead to wrong LCAs.
# - Second Best Minimum Spanning Tree (graph, tree, enumeration)
#   • When to use: Use this when you need to identify an alternative network configuration that is marginally more expensive than the optimal one, or for robustness analysis in network design.
#   • Idea: This algorithm identifies the spanning tree with the second minimum total edge weight by finding the primary MST and then systematically replacing one MST edge with a non-MST edge. The overall time complexity is typically O(E log E + E log V).
#   • Invariants: The primary MST T always connects all vertices with minimum total weight.; Any candidate second-best MST T' is a spanning tree with exactly V-1 edges.
#   • Tips: First compute the primary MST using Kruskal's or Prim's algorithm.; For each non-MST edge (u, v), adding it to the MST creates a unique cycle.
#   • Pitfalls: Incorrectly identifying the heaviest edge on the cycle formed by adding a non-MST edge.; Forgetting to handle disconnected graphs (MST implies connected).
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
    def btreeGameWinningMove(self, root, n, x):
        """
        :type root: Optional[TreeNode]
        :type n: int
        :type x: int
        :rtype: bool
        """
        # Helper function to perform DFS and find the node with value x
        def dfs(node):
            if not node:
                return 0
            left_size = dfs(node.left)
            right_size = dfs(node.right)
            if node.val == x:
                self.left_subtree_size = left_size
                self.right_subtree_size = right_size
            return left_size + right_size + 1
        
        self.left_subtree_size = 0
        self.right_subtree_size = 0
        
        # Perform DFS to find sizes of left and right subtrees of node x
        dfs(root)
        
        # Calculate the size of the "parent" part of the tree
        parent_size = n - (self.left_subtree_size + self.right_subtree_size + 1)
        
        # Check if any of the three parts is greater than half of n
        max_part_size = max(self.left_subtree_size, self.right_subtree_size, parent_size)
        
        return max_part_size > n // 2