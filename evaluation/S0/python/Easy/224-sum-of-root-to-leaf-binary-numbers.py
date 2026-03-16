# Source: https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/   |   Difficulty: Easy
#
# Problem Description:
# You are given the root of a binary tree where each node has a value 0 or 1. Each root-to-leaf path represents a binary number starting with the most significant bit.
#
#
# 	For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could represent 01101 in binary, which is 13.
#
#
# For all leaves in the tree, consider the numbers represented by the path from the root to that leaf. Return the sum of these numbers.
#
# The test cases are generated so that the answer fits in a 32-bits integer.
#
# Example:
# Input: root = [1,0,1,0,1,0,1]
# Output: 22
# Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22
#
# Constraints:
# The number of nodes in the tree is in the range [1, 1000].
# 	Node.val is 0 or 1.
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def sumRootToLeaf(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        def dfs(node, current_value):
            if not node:
                return 0
            
            current_value = (current_value << 1) | node.val
            
            # If it's a leaf node, return the current value
            if not node.left and not node.right:
                return current_value
            
            # Recur for left and right subtrees
            left_sum = dfs(node.left, current_value)
            right_sum = dfs(node.right, current_value)
            
            return left_sum + right_sum
        
        return dfs(root, 0)