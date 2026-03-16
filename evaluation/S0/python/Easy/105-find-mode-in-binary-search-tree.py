# Source: https://leetcode.com/problems/find-mode-in-binary-search-tree/   |   Difficulty: Easy
#
# Problem Description:
# Given the root of a binary search tree (BST) with duplicates, return all the mode(s) (i.e., the most frequently occurred element) in it.
#
# If the tree has more than one mode, return them in any order.
#
# Assume a BST is defined as follows:
#
#
# 	The left subtree of a node contains only nodes with keys less than or equal to the node's key.
# 	The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
# 	Both the left and right subtrees must also be binary search trees.
#
# Example:
# Input: root = [1,null,2,2]
# Output: [2]
#
# Constraints:
# The number of nodes in the tree is in the range [1, 104].
# 	-105 <= Node.val <= 105
#
#
#  
# Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def findMode(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[int]
        """
        if not root:
            return []
        
        self.prev = None
        self.count = 0
        self.max_count = 0
        self.modes = []
        
        def inorder(node):
            if not node:
                return
            
            inorder(node.left)
            
            # Process current node
            if self.prev is None or self.prev.val != node.val:
                self.count = 1
            else:
                self.count += 1
            
            if self.count > self.max_count:
                self.max_count = self.count
                self.modes = [node.val]
            elif self.count == self.max_count:
                self.modes.append(node.val)
            
            self.prev = node
            
            inorder(node.right)
        
        inorder(root)
        return self.modes