# Source: https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/   |   Difficulty: Hard
#
# Problem Description:
# Given the root of a binary tree, calculate the vertical order traversal of the binary tree.
#
# For each node at position (row, col), its left and right children will be at positions (row + 1, col - 1) and (row + 1, col + 1) respectively. The root of the tree is at (0, 0).
#
# The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column index starting from the leftmost column and ending on the rightmost column. There may be multiple nodes in the same row and same column. In such a case, sort these nodes by their values.
#
# Return the vertical order traversal of the binary tree.
#
# Example:
# Input: root = [3,9,20,null,null,15,7]
# Output: [[9],[3,15],[20],[7]]
# Explanation:
# Column -1: Only node 9 is in this column.
# Column 0: Nodes 3 and 15 are in this column in that order from top to bottom.
# Column 1: Only node 20 is in this column.
# Column 2: Only node 7 is in this column.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 1000].
# 	0 <= Node.val <= 1000
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def verticalTraversal(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[List[int]]
        """
        nodes = []
        
        def dfs(node, row, col):
            if node:
                nodes.append((col, row, node.val))
                dfs(node.left, row + 1, col - 1)
                dfs(node.right, row + 1, col + 1)
        
        dfs(root, 0, 0)
        nodes.sort()
        
        result = []
        last_col = float('-inf')
        
        for col, row, value in nodes:
            if col != last_col:
                result.append([])
                last_col = col
            result[-1].append(value)
        
        return result