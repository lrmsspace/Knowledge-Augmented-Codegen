# Source: https://leetcode.com/problems/merge-bsts-to-create-single-bst/   |   Difficulty: Hard
#
# Problem Description:
# You are given n BST (binary search tree) root nodes for n separate BSTs stored in an array trees (0-indexed). Each BST in trees has at most 3 nodes, and no two roots have the same value. In one operation, you can:
#
#
# 	Select two distinct indices i and j such that the value stored at one of the leaves of trees[i] is equal to the root value of trees[j].
# 	Replace the leaf node in trees[i] with trees[j].
# 	Remove trees[j] from trees.
#
#
# Return the root of the resulting BST if it is possible to form a valid BST after performing n - 1 operations, or null if it is impossible to create a valid BST.
#
# A BST (binary search tree) is a binary tree where each node satisfies the following property:
#
#
# 	Every node in the node's left subtree has a value strictly less than the node's value.
# 	Every node in the node's right subtree has a value strictly greater than the node's value.
#
#
# A leaf is a node that has no children.
#
# Example:
# Input: trees = [[2,1],[3,2,5],[5,4]]
# Output: [3,2,5,1,null,4]
# Explanation:
# In the first operation, pick i=1 and j=0, and merge trees[0] into trees[1].
# Delete trees[0], so trees = [[3,2,5,1],[5,4]].
#
# In the second operation, pick i=0 and j=1, and merge trees[1] into trees[0].
# Delete trees[1], so trees = [[3,2,5,1,null,4]].
#
# The resulting tree, shown above, is a valid BST, so return its root.
#
# Constraints:
# n == trees.length
# 	1 <= n <= 5 * 104
# 	The number of nodes in each tree is in the range [1, 3].
# 	Each node in the input may have children but no grandchildren.
# 	No two roots of trees have the same value.
# 	All the trees in the input are valid BSTs.
# 	1 <= TreeNode.val <= 5 * 104.
#
# Helpful references (internal KB):
# - Prüfer code (tree, heap, simulation, greedy)
#   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
#   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
#   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
#   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
#   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
# - Balanced Search Trees (tree, ds, recursion)
#   • When to use: When needing a self-balancing search tree that guarantees logarithmic time complexity for search and insertion operations. Useful for maintaining data in sorted order with consistent performance, especially when frequent updates are expected.
#   • Idea: A 2-3 tree is a self-balancing search tree where every node has either two children (a 2-node) or three children (a 3-node), ensuring all leaves are at the same depth. It guarantees O(log N) time complexity for search, insertion, and deletion operations.
#   • Invariants: All leaves are at the same depth from the root.; Every node is either a 2-node (one key, two children) or a 3-node (two keys, three children).
#   • Tips: Understand the two node types: 2-nodes (one key, two children) and 3-nodes (two keys, three children).; Insertion always starts by finding the leaf position, then propagates splits upwards if a 4-node is formed.
#   • Pitfalls: Incorrectly handling the promotion of keys during node splits can break the tree's structure.; Forgetting to update parent links after a node split or merge operation.
# - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, lca)
#   • When to use: Use this technique for efficiently answering multiple Range Minimum Queries on a static array, especially when an asymptotically optimal O(1) query time solution is required.
#   • Idea: This algorithm solves the static Range Minimum Query problem by first constructing a Cartesian tree from the input array, then reducing RMQ queries to Lowest Common Ancestor queries on this tree. It achieves an optimal O(N) preprocessing time and O(1) query time.
#   • Invariants: For any node `u` in the Cartesian tree, `value(u)` is the minimum among all values in the original array segment represented by `u`'s subtree.; The in-order traversal of the Cartesian tree nodes' original array indices yields the original array `A`'s indices in increasing order.
#   • Tips: Construct the Cartesian tree efficiently in O(N) time, typically using a stack-based approach.; The value of the LCA of two nodes in the Cartesian tree corresponds to the minimum in the original array range between their indices.
#   • Pitfalls: Incorrectly building the Cartesian tree, especially when handling duplicate values or edge cases like empty arrays.; The Farach-Colton and Bender LCA algorithm is complex to implement and often requires significant effort.
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
    def canMerge(self, trees):
        """
        :type trees: List[TreeNode]
        :rtype: TreeNode
        """
        # Step 1: Build a mapping from root values to their corresponding trees
        root_map = {tree.val: tree for tree in trees}
        
        # Step 2: Count the occurrences of each value across all trees
        value_count = {}
        for tree in trees:
            value_count[tree.val] = value_count.get(tree.val, 0) + 1
            if tree.left:
                value_count[tree.left.val] = value_count.get(tree.left.val, 0) + 1
            if tree.right:
                value_count[tree.right.val] = value_count.get(tree.right.val, 0) + 1
        
        # Step 3: Identify the unique root (the one that appears only once)
        root = None
        for val, count in value_count.items():
            if count == 1:
                if root is not None:
                    return None  # More than one unique root found
                root = root_map[val]
        
        if root is None:
            return None  # No unique root found
        
        # Step 4: Merge the trees into the identified root
        def merge(node):
            if node is None:
                return True
            
            if node.left and node.left.val in root_map:
                node.left = root_map[node.left.val]
                del root_map[node.left.val]
            
            if node.right and node.right.val in root_map:
                node.right = root_map[node.right.val]
                del root_map[node.right.val]
            
            return merge(node.left) and merge(node.right)
        
        if not merge(root):
            return None
        
        # Step 5: Check if all trees have been merged
        return root if not root_map else None