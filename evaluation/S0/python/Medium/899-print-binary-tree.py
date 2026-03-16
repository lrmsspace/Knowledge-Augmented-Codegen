# Source: https://leetcode.com/problems/print-binary-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, construct a 0-indexed m x n string matrix res that represents a formatted layout of the tree. The formatted layout matrix should be constructed using the following rules:
#
#
# 	The height of the tree is height and the number of rows m should be equal to height + 1.
# 	The number of columns n should be equal to 2height+1 - 1.
# 	Place the root node in the middle of the top row (more formally, at location res[0][(n-1)/2]).
# 	For each node that has been placed in the matrix at position res[r][c], place its left child at res[r+1][c-2height-r-1] and its right child at res[r+1][c+2height-r-1].
# 	Continue this process until all the nodes in the tree have been placed.
# 	Any empty cells should contain the empty string "".
#
#
# Return the constructed matrix res.
#
# Example:
# Input: root = [1,2]
# Output: 
# [["","1",""],
#  ["2","",""]]
#
# Constraints:
# The number of nodes in the tree is in the range [1, 210].
# 	-99 <= Node.val <= 99
# 	The depth of the tree will be in the range [1, 10].
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def printTree(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[List[str]]
        """
        def getHeight(node):
            if not node:
                return 0
            return 1 + max(getHeight(node.left), getHeight(node.right))
        
        height = getHeight(root)
        m = height
        n = (1 << height) - 1  # 2^height - 1
        res = [["" for _ in range(n)] for _ in range(m)]
        
        def fill(node, r, c, h):
            if not node:
                return
            res[r][c] = str(node.val)
            offset = 1 << (h - r - 1)  # 2^(h - r - 1)
            fill(node.left, r + 1, c - offset, h)
            fill(node.right, r + 1, c + offset, h)
        
        fill(root, 0, (n - 1) // 2, height)
        return res