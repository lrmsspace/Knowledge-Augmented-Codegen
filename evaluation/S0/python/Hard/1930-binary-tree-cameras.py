# Source: https://leetcode.com/problems/binary-tree-cameras/   |   Difficulty: Hard
#
# Problem Description:
# You are given the root of a binary tree. We install cameras on the tree nodes where each camera at a node can monitor its parent, itself, and its immediate children.
#
# Return the minimum number of cameras needed to monitor all nodes of the tree.
#
# Example:
# Input: root = [0,0,null,0,0]
# Output: 1
# Explanation: One camera is enough to monitor all nodes if placed as shown.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 1000].
# 	Node.val == 0
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def minCameraCover(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        self.camera_count = 0
        
        def dfs(node):
            if not node:
                return 1  # Null nodes are considered covered
            
            left = dfs(node.left)
            right = dfs(node.right)
            
            if left == 0 or right == 0:
                self.camera_count += 1
                return 2  # Place a camera here
            
            if left == 2 or right == 2:
                return 1  # This node is covered
            
            return 0  # This node is not covered
        
        if dfs(root) == 0:
            self.camera_count += 1
        
        return self.camera_count