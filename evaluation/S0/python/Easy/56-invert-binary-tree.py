# Source: https://leetcode.com/problems/invert-binary-tree/   |   Difficulty: Easy
#
# Problem Description:
# Given the root of a binary tree, invert the tree, and return its root.
#
# Example:
# Input: root = [4,2,7,1,3,6,9]
# Output: [4,7,2,9,6,3,1]
#
# Constraints:
# The number of nodes in the tree is in the range [0, 100].
# 	-100 <= Node.val <= 100
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def invertTree(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: Optional[TreeNode]
        """
        if root is None:
            return None
        
        # Swap the left and right children
        root.left, root.right = root.right, root.left
        
        # Recursively invert the left and right subtrees
        self.invertTree(root.left)
        self.invertTree(root.right)
        
        return root