# Source: https://leetcode.com/problems/binary-tree-postorder-traversal/   |   Difficulty: Easy
#
# Problem Description:
# Given the root of a binary tree, return the postorder traversal of its nodes' values.
#
# Example:
# Input: root = [1,null,2,3]
#
# Output: [3,2,1]
#
# Explanation:
#
# Constraints:
# The number of the nodes in the tree is in the range [0, 100].
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
    def postorderTraversal(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[int]
        """
        result = []
        stack = []
        last_visited = None
        current = root

        while current or stack:
            while current:
                stack.append(current)
                current = current.left

            peek_node = stack[-1]
            # if right child exists and traversing node from left child, move right
            if peek_node.right and last_visited != peek_node.right:
                current = peek_node.right
            else:
                result.append(peek_node.val)
                last_visited = stack.pop()

        return result