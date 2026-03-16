# Source: https://leetcode.com/problems/insufficient-nodes-in-root-to-leaf-paths/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree and an integer limit, delete all insufficient nodes in the tree simultaneously, and return the root of the resulting binary tree.
#
# A node is insufficient if every root to leaf path intersecting this node has a sum strictly less than limit.
#
# A leaf is a node with no children.
#
# Example:
# Input: root = [1,2,3,4,-99,-99,7,8,9,-99,-99,12,13,-99,14], limit = 1
# Output: [1,2,3,4,null,null,7,8,9,null,14]
#
# Constraints:
# The number of nodes in the tree is in the range [1, 5000].
# 	-105 <= Node.val <= 105
# 	-109 <= limit <= 109
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def sufficientSubset(self, root, limit):
        """
        :type root: Optional[TreeNode]
        :type limit: int
        :rtype: Optional[TreeNode]
        """
        def dfs(node, curr_sum):
            if not node:
                return True
            
            curr_sum += node.val
            
            if not node.left and not node.right:
                return curr_sum < limit
            
            left_insufficient = dfs(node.left, curr_sum)
            right_insufficient = dfs(node.right, curr_sum)
            
            if left_insufficient:
                node.left = None
            if right_insufficient:
                node.right = None
            
            return left_insufficient and right_insufficient
        
        if dfs(root, 0):
            return None
        return root