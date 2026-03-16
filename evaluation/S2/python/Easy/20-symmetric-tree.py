# Source: https://leetcode.com/problems/symmetric-tree/   |   Difficulty: Easy
#
# Problem Description:
# Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).
#
# Example:
# Input: root = [1,2,2,3,4,4,3]
# Output: true
#
# Constraints:
# The number of nodes in the tree is in the range [1, 1000].
# 	-100 <= Node.val <= 100
#
#
#  
# Follow up: Could you solve it both recursively and iteratively?
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
    def isSymmetric(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: bool
        """
        def isMirror(left, right):