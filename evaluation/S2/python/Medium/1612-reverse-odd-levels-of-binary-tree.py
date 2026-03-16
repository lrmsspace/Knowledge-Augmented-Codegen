# Source: https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a perfect binary tree, reverse the node values at each odd level of the tree.
#
#
# 	For example, suppose the node values at level 3 are [2,1,3,4,7,11,29,18], then it should become [18,29,11,7,4,3,1,2].
#
#
# Return the root of the reversed tree.
#
# A binary tree is perfect if all parent nodes have two children and all leaves are on the same level.
#
# The level of a node is the number of edges along the path between it and the root node.
#
# Example:
# Input: root = [2,3,5,8,13,21,34]
# Output: [2,5,3,8,13,21,34]
# Explanation: 
# The tree has only one odd level.
# The nodes at level 1 are 3, 5 respectively, which are reversed and become 5, 3.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 214].
# 	0 <= Node.val <= 105
# 	root is a perfect binary tree.
#
# Helpful references (internal KB):
# - Sqrt Tree (array, tree, recursion)
#   • When to use: When you need to perform O(1) range queries and support efficient updates (single element or range) on an array, leveraging a hierarchical decomposition.
#   • Idea: A Sqrt Tree is a data structure that supports O(1) range queries and efficient updates on an array. It recursively decomposes the array into blocks and layers, using precomputed information and bitwise operations to quickly answer queries and propagate updates.
#   • Invariants: Each element is part of exactly one block at each layer of the Sqrt Tree.; The highest differing bit between `l` and `r` identifies the specific layer for processing `q(l, r)`.
#   • Tips: Precompute highest bit for efficient layer selection.; Decompose queries into intra-block and inter-block segments.
#   • Pitfalls: Naive updates can result in O(N) complexity per update.; High memory consumption due to multiple layers of precomputed arrays.
# - Check whether a graph is bipartite (graph, queue, bfs)
#   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
#   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
#   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
#   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
#   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
# - Gray code (number, simulation)
#   • When to use: Use when generating a sequence of numbers where adjacent values must differ by only one bit, or for error detection in digital systems. It is also useful for certain combinatorial problems.
#   • Idea: Gray code is a binary numeral system where two successive values differ in exactly one bit position. It can be generated efficiently using bitwise operations in O(1) time per code, or O(N) for N codes.
#   • Invariants: The number of bits in the generated Gray code G(n) is equal to the number of bits in the input binary n.; G(0) is always 0, and G(1) is always 1.
#   • Tips: The most common formula for converting binary n to Gray code G(n) is G(n) = n ^ (n >> 1).; To convert Gray code G(n) back to binary n, use a series of XOR operations: n = G(n) ^ (G(n) >> 1) ^ (G(n) >> 2) ^ ... until zero.
#   • Pitfalls: Confusing Gray code with standard binary representation, which can have multiple bit changes between successive numbers.; Incorrectly implementing the conversion formulas, especially the Gray to binary conversion.
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
    def reverseOddLevels(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: Optional[TreeNode]
        """
        if not root:
            return None
        
        queue = [root]
        level = 0
        
        while queue:
            level_size = len(queue)
            current_level_nodes = []
            
            for _ in range(level_size):
                node = queue.pop(0)
                current_level_nodes.append(node)
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            if level % 2 == 1:  # Reverse values at odd levels
                left, right = 0, len(current_level_nodes) - 1
                while left < right:
                    current_level_nodes[left].val, current_level_nodes[right].val = current_level_nodes[right].val, current_level_nodes[left].val
                    left += 1
                    right -= 1
            
            level += 1
        
        return root