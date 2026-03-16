# Source: https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/   |   Difficulty: Medium
#
# Problem Description:
# You are given the root of a binary tree with n nodes. Each node is uniquely assigned a value from 1 to n. You are also given an integer startValue representing the value of the start node s, and a different integer destValue representing the value of the destination node t.
#
# Find the shortest path starting from node s and ending at node t. Generate step-by-step directions of such path as a string consisting of only the uppercase letters 'L', 'R', and 'U'. Each letter indicates a specific direction:
#
#
# 	'L' means to go from a node to its left child node.
# 	'R' means to go from a node to its right child node.
# 	'U' means to go from a node to its parent node.
#
#
# Return the step-by-step directions of the shortest path from node s to node t.
#
# Example:
# Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
# Output: "UURL"
# Explanation: The shortest path is: 3 → 1 → 5 → 2 → 6.
#
# Constraints:
# The number of nodes in the tree is n.
# 	2 <= n <= 105
# 	1 <= Node.val <= n
# 	All the values in the tree are unique.
# 	1 <= startValue, destValue <= n
# 	startValue != destValue
#
# Helpful references (internal KB):
# - Depth First Search (tree, graph, dfs)
#   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
#   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
#   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
#   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
#   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
# - Lyndon factorization (string, greedy, two-pointers)
#   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
#   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
#   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
#   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
#   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
# - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
#   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
#   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
#   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
#   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
#   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
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
    def getDirections(self, root, startValue, destValue):
        """
        :type root: Optional[TreeNode]
        :type startValue: int
        :type destValue: int
        :rtype: str
        """
        parent = {}
        def dfs(node, par):
            if not node:
                return
            parent[node.val] = par
            dfs(node.left, node)
            dfs(node.right, node)
        
        dfs(root, None)
        
        path_to_root = {}
        cur = startValue
        steps = 0
        while cur is not None:
            path_to_root[cur] = steps
            steps += 1
            cur = parent[cur].val if parent[cur] else None
        
        cur = destValue
        lca_steps = 0
        while cur not in path_to_root:
            lca_steps += 1
            cur = parent[cur].val if parent[cur] else None
        
        total_steps = path_to_root[cur] + lca_steps
        directions = []
        
        for _ in range(path_to_root[cur]):
            directions.append('U')
        
        def get_path(from_node, to_node):
            path = []
            def dfs_path(node):
                if not node:
                    return False
                if node.val == to_node:
                    return True
                if dfs_path(node.left):
                    path.append('L')
                    return True
                if dfs_path(node.right):
                    path.append('R')
                    return True
                return False
            
            dfs_path(from_node)
            return path[::-1]
        
        lca_node = self.find_node(root, cur)
        directions.extend(get_path(lca_node, destValue))
        
        return ''.join(directions)