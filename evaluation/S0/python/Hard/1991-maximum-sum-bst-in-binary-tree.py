# Source: https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/   |   Difficulty: Hard
#
# Problem Description:
# Given a binary tree root, return the maximum sum of all keys of any sub-tree which is also a Binary Search Tree (BST).
#
# Assume a BST is defined as follows:
#
#
# 	The left subtree of a node contains only nodes with keys less than the node's key.
# 	The right subtree of a node contains only nodes with keys greater than the node's key.
# 	Both the left and right subtrees must also be binary search trees.
#
# Example:
# Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
# Output: 20
# Explanation: Maximum sum in a valid Binary search tree is obtained in root node with key equal to 3.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 4 * 104].
# 	-4 * 104 <= Node.val <= 4 * 104
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def maxSumBST(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        self.max_sum = 0

        def helper(node):
            if not node:
                return (True, float('inf'), float('-inf'), 0)

            left_is_bst, left_min, left_max, left_sum = helper(node.left)
            right_is_bst, right_min, right_max, right_sum = helper(node.right)

            if left_is_bst and right_is_bst and left_max < node.val < right_min:
                current_sum = left_sum + right_sum + node.val
                self.max_sum = max(self.max_sum, current_sum)
                return (True,
                        min(left_min, node.val),
                        max(right_max, node.val),
                        current_sum)
            else:
                return (False, 0, 0, 0)

        helper(root)
        return self.max_sum