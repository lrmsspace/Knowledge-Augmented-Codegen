# Source: https://leetcode.com/problems/univalued-binary-tree/   |   Difficulty: Easy
#
# Problem Description:
# A binary tree is uni-valued if every node in the tree has the same value.
#
# Given the root of a binary tree, return true if the given tree is uni-valued, or false otherwise.
#
# Example:
# Input: root = [1,1,1,1,1,null,1]
# Output: true
#
# Constraints:
# The number of nodes in the tree is in the range [1, 100].
# 	0 <= Node.val < 100
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def isUnivalTree(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: bool
        """
        if not root:
            return True
        
        value = root.val
        stack = [root]
        
        while stack:
            node = stack.pop()
            if node.val != value:
                return False
            if node.left:
                stack.append(node.left)
            if node.right:
                stack.append(node.right)
        
        return True