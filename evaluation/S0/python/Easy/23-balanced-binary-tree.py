# Source: https://leetcode.com/problems/balanced-binary-tree/   |   Difficulty: Easy
#
# Problem Description:
# Given a binary tree, determine if it is height-balanced.
#
# Example:
# Input: root = [3,9,20,null,null,15,7]
# Output: true
#
# Constraints:
# The number of nodes in the tree is in the range [0, 5000].
# 	-104 <= Node.val <= 104
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def isBalanced(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: bool
        """
        def check_balance_and_height(node):
            if not node:
                return True, 0
            
            left_balanced, left_height = check_balance_and_height(node.left)
            right_balanced, right_height = check_balance_and_height(node.right)
            
            current_balanced = (left_balanced and right_balanced and 
                                abs(left_height - right_height) <= 1)
            current_height = 1 + max(left_height, right_height)
            
            return current_balanced, current_height
        
        balanced, _ = check_balance_and_height(root)
        return balanced