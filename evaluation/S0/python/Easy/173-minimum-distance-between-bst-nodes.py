# Source: https://leetcode.com/problems/minimum-distance-between-bst-nodes/   |   Difficulty: Easy
#
# Problem Description:
# Given the root of a Binary Search Tree (BST), return the minimum difference between the values of any two different nodes in the tree.
#
# Example:
# Input: root = [4,2,6,1,3]
# Output: 1
#
# Constraints:
# The number of nodes in the tree is in the range [2, 100].
# 	0 <= Node.val <= 105
#
#
#  
# Note: This question is the same as 530: https://leetcode.com/problems/minimum-absolute-difference-in-bst/
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def minDiffInBST(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        self.prev = None
        self.min_diff = float('inf')
        
        def inorder(node):
            if not node:
                return
            
            inorder(node.left)
            
            if self.prev is not None:
                self.min_diff = min(self.min_diff, node.val - self.prev)
            self.prev = node.val
            
            inorder(node.right)
        
        inorder(root)
        return self.min_diff