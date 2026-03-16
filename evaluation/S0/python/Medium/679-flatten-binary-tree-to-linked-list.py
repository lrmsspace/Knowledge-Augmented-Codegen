# Source: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, flatten the tree into a "linked list":
#
#
# 	The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
# 	The "linked list" should be in the same order as a pre-order traversal of the binary tree.
#
# Example:
# Input: root = [1,2,5,3,4,null,6]
# Output: [1,null,2,null,3,null,4,null,5,null,6]
#
# Constraints:
# The number of nodes in the tree is in the range [0, 2000].
# 	-100 <= Node.val <= 100
#
#
#  
# Follow up: Can you flatten the tree in-place (with O(1) extra space)?
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def flatten(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: None Do not return anything, modify root in-place instead.
        """
        if not root:
            return
        
        stack = [root]
        prev = None
        
        while stack:
            node = stack.pop()
            
            if prev:
                prev.left = None
                prev.right = node
            
            if node.right:
                stack.append(node.right)
            if node.left:
                stack.append(node.left)
            
            prev = node