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
        from collections import defaultdict
        
        val_to_tree = {}
        child_vals = set()
        
        for tree in trees:
            val_to_tree[tree.val] = tree
            if tree.left:
                child_vals.add(tree.left.val)
            if tree.right:
                child_vals.add(tree.right.val)
        
        root_candidates = [tree for tree in trees if tree.val not in child_vals]
        if len(root_candidates) != 1:
            return None
        
        root = root_candidates[0]
        
        def merge(node):
            if not node:
                return True
            
            if node.left and node.left.val in val_to_tree:
                node.left = val_to_tree[node.left.val]
                del val_to_tree[node.left.val]
                if not merge(node.left):
                    return False
            
            if node.right and node.right.val in val_to_tree:
                node.right = val_to_tree[node.right.val]
                del val_to_tree[node.right.val]
                if not merge(node.right):
                    return False
            
            return True
        
        if not merge(root) or val_to_tree:
            return None
        
        def is_bst(node, low, high):
            if not node:
                return True
            if not (low < node.val < high):
                return False
            return is_bst(node.left, low, node.val) and is_bst(node.right, node.val, high)
        
        return root if is_bst(root, float('-inf'), float('inf')) else None