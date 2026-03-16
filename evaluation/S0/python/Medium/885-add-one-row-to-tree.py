# Source: https://leetcode.com/problems/add-one-row-to-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree and two integers val and depth, add a row of nodes with value val at the given depth depth.
#
# Note that the root node is at depth 1.
#
# The adding rule is:
#
#
# 	Given the integer depth, for each not null tree node cur at the depth depth - 1, create two tree nodes with value val as cur's left subtree root and right subtree root.
# 	cur's original left subtree should be the left subtree of the new left subtree root.
# 	cur's original right subtree should be the right subtree of the new right subtree root.
# 	If depth == 1 that means there is no depth depth - 1 at all, then create a tree node with value val as the new root of the whole original tree, and the original tree is the new root's left subtree.
#
# Example:
# Input: root = [4,2,6,3,1,5], val = 1, depth = 2
# Output: [4,1,1,2,null,null,6,3,1,5]
#
# Constraints:
# The number of nodes in the tree is in the range [1, 104].
# 	The depth of the tree is in the range [1, 104].
# 	-100 <= Node.val <= 100
# 	-105 <= val <= 105
# 	1 <= depth <= the depth of tree + 1
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def addOneRow(self, root, val, depth):
        """
        :type root: Optional[TreeNode]
        :type val: int
        :type depth: int
        :rtype: Optional[TreeNode]
        """
        if depth == 1:
            new_root = TreeNode(val)
            new_root.left = root
            return new_root
        
        def dfs(node, current_depth):
            if not node:
                return
            
            if current_depth == depth - 1:
                old_left = node.left
                old_right = node.right
                
                node.left = TreeNode(val)
                node.left.left = old_left
                
                node.right = TreeNode(val)
                node.right.right = old_right
            else:
                dfs(node.left, current_depth + 1)
                dfs(node.right, current_depth + 1)
        
        dfs(root, 1)
        return root