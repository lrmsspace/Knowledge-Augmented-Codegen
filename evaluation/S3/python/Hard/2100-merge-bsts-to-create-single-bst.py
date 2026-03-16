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
#   • When to use: Use when counting labeled trees or converting between a labeled tree and a unique sequence representation for combinatorial analysis. It provides a bijection for problems involving N labeled nodes.
#   • Idea: Prüfer code is a unique sequence of length N-2 that represents a labeled tree with N nodes. It is constructed by iteratively removing the smallest-labeled leaf and recording its neighbor, and can be reconstructed back into the tree.
#   • Invariants: The Prüfer sequence always contains N-2 elements for a tree with N nodes.; At each step of encoding, the removed node is a leaf with the smallest label among all current leaves.
#   • Tips: Maintain an array of node degrees for efficient updates.; Use a min-priority queue to quickly find the smallest-labeled leaf.
#   • Pitfalls: Incorrectly updating node degrees after removal.; Off-by-one errors when dealing with 0-indexed vs. 1-indexed labels.
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
#   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
#   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
#   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
#   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
#   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
#   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
#   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
#   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
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
        
        # Step 2: Count the occurrences of each value in the trees
        value_count = {}
        for tree in trees:
            value_count[tree.val] = value_count.get(tree.val, 0) + 1
            if tree.left:
                value_count[tree.left.val] = value_count.get(tree.left.val, 0) + 1
            if tree.right:
                value_count[tree.right.val] = value_count.get(tree.right.val, 0) + 1
        
        # Step 3: Identify the unique root (the one that appears only once)
        root_candidates = [val for val, count in value_count.items() if count == 1]
        if len(root_candidates) != 1:
            return None
        
        root_val = root_candidates[0]
        root = root_map[root_val]
        
        # Step 4: Merge trees using DFS
        def merge(node):
            if not node:
                return True
            
            if node.val in root_map and node != root:
                subtree = root_map[node.val]
                node.left, node.right = subtree.left, subtree.right
                del root_map[node.val]
            
            return merge(node.left) and merge(node.right)
        
        if not merge(root):
            return None
        
        # Step 5: Check if all trees have been merged
        return root if not root_map else None