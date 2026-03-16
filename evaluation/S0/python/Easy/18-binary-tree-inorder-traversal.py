# Source: https://leetcode.com/problems/binary-tree-inorder-traversal/   |   Difficulty: Easy
#
# Problem Description:
# Given the root of a binary tree, return the inorder traversal of its nodes' values.
#
# Example:
# Input: root = [1,null,2,3]
#
# Output: [1,3,2]
#
# Explanation:
#
# Constraints:
# The number of nodes in the tree is in the range [0, 100].
# 	-100 <= Node.val <= 100
#
#
#  
# Follow up: Recursive solution is trivial, could you do it iteratively?
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def inorderTraversal(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[int]
        """
        res = []
        stack = []
        curr = root
        
        while curr or stack:
            while curr:
                stack.append(curr)
                curr = curr.left
            curr = stack.pop()
            res.append(curr.val)
            curr = curr.right
        
        return res