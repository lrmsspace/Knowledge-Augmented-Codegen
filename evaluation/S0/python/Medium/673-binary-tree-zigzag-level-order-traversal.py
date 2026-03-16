# Source: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).
#
# Example:
# Input: root = [3,9,20,null,null,15,7]
# Output: [[3],[20,9],[15,7]]
#
# Constraints:
# The number of nodes in the tree is in the range [0, 2000].
# 	-100 <= Node.val <= 100
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def zigzagLevelOrder(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[List[int]]
        """
        if not root:
            return []
        
        result = []
        current_level = [root]
        left_to_right = True
        
        while current_level:
            level_values = []
            next_level = []
            
            for node in current_level:
                level_values.append(node.val)
                if node.left:
                    next_level.append(node.left)
                if node.right:
                    next_level.append(node.right)
            
            if not left_to_right:
                level_values.reverse()
            
            result.append(level_values)
            current_level = next_level
            left_to_right = not left_to_right
        
        return result