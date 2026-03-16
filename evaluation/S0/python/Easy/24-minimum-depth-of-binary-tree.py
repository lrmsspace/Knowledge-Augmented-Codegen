# Source: https://leetcode.com/problems/minimum-depth-of-binary-tree/   |   Difficulty: Easy
#
# Problem Description:
# Given a binary tree, find its minimum depth.
#
# The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
#
# Note: A leaf is a node with no children.
#
# Example:
# Input: root = [3,9,20,null,null,15,7]
# Output: 2
#
# Constraints:
# The number of nodes in the tree is in the range [0, 105].
# 	-1000 <= Node.val <= 1000
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def minDepth(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        if not root:
            return 0
        
        left_depth = self.minDepth(root.left)
        right_depth = self.minDepth(root.right)
        
        # If one of the subtrees is missing, we should not consider its depth
        if not root.left or not root.right:
            return 1 + max(left_depth, right_depth)
        
        return 1 + min(left_depth, right_depth)