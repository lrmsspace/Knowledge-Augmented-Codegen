# Source: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/   |   Difficulty: Medium
#
# Problem Description:
# Given two integer arrays, preorder and postorder where preorder is the preorder traversal of a binary tree of distinct values and postorder is the postorder traversal of the same tree, reconstruct and return the binary tree.
#
# If there exist multiple answers, you can return any of them.
#
# Example:
# Input: preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
# Output: [1,2,3,4,5,6,7]
#
# Constraints:
# 1 <= preorder.length <= 30
# 	1 <= preorder[i] <= preorder.length
# 	All the values of preorder are unique.
# 	postorder.length == preorder.length
# 	1 <= postorder[i] <= postorder.length
# 	All the values of postorder are unique.
# 	It is guaranteed that preorder and postorder are the preorder traversal and postorder traversal of the same binary tree.
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def constructFromPrePost(self, preorder, postorder):
        """
        :type preorder: List[int]
        :type postorder: List[int]
        :rtype: Optional[TreeNode]
        """
        if not preorder or not postorder:
            return None
        
        root = TreeNode(preorder[0])
        
        if len(preorder) == 1:
            return root
        
        left_subtree_root_val = preorder[1]
        left_subtree_size = postorder.index(left_subtree_root_val) + 1
        
        root.left = self.constructFromPrePost(
            preorder[1:left_subtree_size + 1],
            postorder[:left_subtree_size]
        )
        
        root.right = self.constructFromPrePost(
            preorder[left_subtree_size + 1:],
            postorder[left_subtree_size:-1]
        )
        
        return root