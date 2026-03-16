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
        if not root:
            return True
        
        def is_mirror(t1, t2):
            if not t1 and not t2:
                return True
            if not t1 or not t2:
                return False
            return (t1.val == t2.val) and is_mirror(t1.left, t2.right) and is_mirror(t1.right, t2.left)
        
        return is_mirror(root.left, root.right)