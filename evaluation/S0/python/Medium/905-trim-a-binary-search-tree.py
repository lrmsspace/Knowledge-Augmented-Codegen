# Source: https://leetcode.com/problems/trim-a-binary-search-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary search tree and the lowest and highest boundaries as low and high, trim the tree so that all its elements lies in [low, high]. Trimming the tree should not change the relative structure of the elements that will remain in the tree (i.e., any node's descendant should remain a descendant). It can be proven that there is a unique answer.
#
# Return the root of the trimmed binary search tree. Note that the root may change depending on the given bounds.
#
# Example:
# Input: root = [1,0,2], low = 1, high = 2
# Output: [1,null,2]
#
# Constraints:
# The number of nodes in the tree is in the range [1, 104].
# 	0 <= Node.val <= 104
# 	The value of each node in the tree is unique.
# 	root is guaranteed to be a valid binary search tree.
# 	0 <= low <= high <= 104
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def trimBST(self, root, low, high):
        """
        :type root: Optional[TreeNode]
        :type low: int
        :type high: int
        :rtype: Optional[TreeNode]
        """
        if not root:
            return None
        
        if root.val < low:
            return self.trimBST(root.right, low, high)
        
        if root.val > high:
            return self.trimBST(root.left, low, high)
        
        root.left = self.trimBST(root.left, low, high)
        root.right = self.trimBST(root.right, low, high)
        
        return root