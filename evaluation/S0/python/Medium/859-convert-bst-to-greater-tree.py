# Source: https://leetcode.com/problems/convert-bst-to-greater-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
#
# As a reminder, a binary search tree is a tree that satisfies these constraints:
#
#
# 	The left subtree of a node contains only nodes with keys less than the node's key.
# 	The right subtree of a node contains only nodes with keys greater than the node's key.
# 	Both the left and right subtrees must also be binary search trees.
#
# Example:
# Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
# Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
#
# Constraints:
# The number of nodes in the tree is in the range [0, 104].
# 	-104 <= Node.val <= 104
# 	All the values in the tree are unique.
# 	root is guaranteed to be a valid binary search tree.
#
#
#  
# Note: This question is the same as 1038: https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def convertBST(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: Optional[TreeNode]
        """
        self.sum = 0
        
        def reverse_inorder(node):
            if not node:
                return
            
            reverse_inorder(node.right)
            self.sum += node.val
            node.val = self.sum
            reverse_inorder(node.left)
        
        reverse_inorder(root)
        return root