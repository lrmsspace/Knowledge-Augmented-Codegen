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
# - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
#   • When to use: Use when you need to find the Lowest Common Ancestor for multiple pairs of nodes in a tree, and all queries are known beforehand. It's an efficient offline approach for batch processing LCA queries.
#   • Idea: Tarjan's offline LCA algorithm uses a Depth-First Search (DFS) traversal combined with a Union-Find data structure to answer all LCA queries efficiently. It processes N nodes and Q queries in O(N + Q * alpha(N)) time, where alpha is the inverse Ackermann function.
#   • Invariants: After visiting a node 'u' and all its children, 'u' is marked as visited.; For any node 'v' whose subtree has been fully processed, 'find_set(v)' returns the representative of 'v''s component.
#   • Tips: Mark nodes as visited during DFS to track processed subtrees.; Use Union-Find's union operation to merge child subtrees with their parent after processing.
#   • Pitfalls: Forgetting to mark nodes as visited, leading to incorrect LCA identification.; Incorrectly updating the 'ancestor' array or 'find_set' logic in Union-Find.
# - Binary Search Trees
#  (tree, enumeration)
#   • When to use: Use when you need to store ordered data in a hierarchical structure that allows for efficient searching, insertion, and deletion operations. It is suitable for dynamic datasets where elements frequently change while maintaining sorted order.
#   • Idea: A Binary Search Tree (BST) is a node-based binary tree data structure where each node has a key, and all keys in the left subtree are less than the node's key, while all keys in the right subtree are greater. Basic operations like search, insertion, and deletion typically have an average time complexity of O(log N) but can degrade to O(N) in the worst case.
#   • Invariants: For every node N, if L is in N's left subtree, then L.key < N.key.; For every node N, if R is in N's right subtree, then R.key > N.key.
#   • Tips: Understand the recursive definition for traversal and operations.; Handle edge cases like empty tree, single node, or leaf nodes carefully.
#   • Pitfalls: Unbalanced trees can lead to O(N) worst-case performance for all operations.; Incorrect handling of duplicate keys can lead to data loss or incorrect structure.
# - Suffix Automaton (graph, tree, string, recursion)
#   • When to use: When needing to efficiently represent all substrings of a string and perform various string operations like counting occurrences, finding distinct substrings, or pattern matching. It is particularly useful for problems involving properties of all substrings or suffixes.
#   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that accepts all suffixes of a given string. It efficiently encodes all substrings and their occurrences, typically constructed in O(N) time and space for a string of length N.
#   • Invariants: Each state in the automaton corresponds to a unique endpos set.; All substrings represented by a state are suffixes of the longest string in that state's endpos set.
#   • Tips: Understand the endpos equivalence classes and suffix links.; Construction is typically incremental, character by character.
#   • Pitfalls: Complexity of implementation can be high due to many edge cases.; Incorrectly handling suffix links during construction.
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
            if count[serial] == 2:  # Only add to result when we see it the second time
                result.append(node)
            return serial
        
        count = defaultdict(int)
        result = []
        serialize(root)
        return result