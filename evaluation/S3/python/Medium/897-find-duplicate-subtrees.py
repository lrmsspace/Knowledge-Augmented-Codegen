# Source: https://leetcode.com/problems/find-duplicate-subtrees/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, return all duplicate subtrees.
#
# For each kind of duplicate subtrees, you only need to return the root node of any one of them.
#
# Two trees are duplicate if they have the same structure with the same node values.
#
# Example:
# Input: root = [1,2,3,4,null,2,4,null,null,4]
# Output: [[2,4],[4]]
#
# Constraints:
# The number of the nodes in the tree will be in the range [1, 5000]
# 	-200 <= Node.val <= 200
#
# Helpful references (internal KB):
# - String Hashing (string, array, hashing, enumeration)
#   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
#   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
#   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
#   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
#   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
# - Suffix Automaton (graph, tree, string, recursion)
#   • When to use: When needing to efficiently represent all substrings of a string and perform various string operations like counting occurrences, finding distinct substrings, or pattern matching. It is particularly useful for problems involving properties of all substrings or suffixes.
#   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that accepts all suffixes of a given string. It efficiently encodes all substrings and their occurrences, typically constructed in O(N) time and space for a string of length N.
#   • Invariants: Each state in the automaton corresponds to a unique endpos set.; All substrings represented by a state are suffixes of the longest string in that state's endpos set.
#   • Tips: Understand the endpos equivalence classes and suffix links.; Construction is typically incremental, character by character.
#   • Pitfalls: Complexity of implementation can be high due to many edge cases.; Incorrectly handling suffix links during construction.
# - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
#   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
#   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
#   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
#   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
#   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
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
    def findDuplicateSubtrees(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[Optional[TreeNode]]
        """
        from collections import defaultdict
        
        def serialize(node):
            if not node:
                return "#"
            left_serial = serialize(node.left)
            right_serial = serialize(node.right)
            serial = f"{node.val},{left_serial},{right_serial}"
            count[serial] += 1
            if count[serial] == 2:
                duplicates.append(node)
            return serial
        
        count = defaultdict(int)
        duplicates = []
        serialize(root)
        return duplicates