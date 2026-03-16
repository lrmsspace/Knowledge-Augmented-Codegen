# Source: https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/   |   Difficulty: Medium
#
# Problem Description:
# You are given the root of a binary tree.
#
# A ZigZag path for a binary tree is defined as follow:
#
#
# 	Choose any node in the binary tree and a direction (right or left).
# 	If the current direction is right, move to the right child of the current node; otherwise, move to the left child.
# 	Change the direction from right to left or from left to right.
# 	Repeat the second and third steps until you can't move in the tree.
#
#
# Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0).
#
# Return the longest ZigZag path contained in that tree.
#
# Example:
# Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1]
# Output: 3
# Explanation: Longest ZigZag path in blue nodes (right -> left -> right).
#
# Constraints:
# The number of nodes in the tree is in the range [1, 5 * 104].
# 	1 <= Node.val <= 100
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def longestZigZag(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        self.ans = 0

        def dfs(node):
            if not node:
                return (-1, -1)  # (left, right)

            left = dfs(node.left)
            right = dfs(node.right)

            left_zigzag = left[1] + 1
            right_zigzag = right[0] + 1

            self.ans = max(self.ans, left_zigzag, right_zigzag)

            return (left_zigzag, right_zigzag)

        dfs(root)
        return self.ans