# Source: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/   |   Difficulty: Medium
#
# Problem Description:
# Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.
#
# Example:
# Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
# Output: [3,9,20,null,null,15,7]
#
# Constraints:
# 1 <= inorder.length <= 3000
# 	postorder.length == inorder.length
# 	-3000 <= inorder[i], postorder[i] <= 3000
# 	inorder and postorder consist of unique values.
# 	Each value of postorder also appears in inorder.
# 	inorder is guaranteed to be the inorder traversal of the tree.
# 	postorder is guaranteed to be the postorder traversal of the tree.
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def buildTree(self, inorder, postorder):
        """
        :type inorder: List[int]
        :type postorder: List[int]
        :rtype: Optional[TreeNode]
        """
        if not inorder or not postorder:
            return None
        
        root_val = postorder.pop()
        root = TreeNode(root_val)
        
        inorder_index = inorder.index(root_val)
        
        root.right = self.buildTree(inorder[inorder_index + 1:], postorder)
        root.left = self.buildTree(inorder[:inorder_index], postorder)
        
        return root