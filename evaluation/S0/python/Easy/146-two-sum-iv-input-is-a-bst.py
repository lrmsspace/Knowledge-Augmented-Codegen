# Source: https://leetcode.com/problems/two-sum-iv-input-is-a-bst/   |   Difficulty: Easy
#
# Problem Description:
# Given the root of a binary search tree and an integer k, return true if there exist two elements in the BST such that their sum is equal to k, or false otherwise.
#
# Example:
# Input: root = [5,3,6,2,4,null,7], k = 9
# Output: true
#
# Constraints:
# The number of nodes in the tree is in the range [1, 104].
# 	-104 <= Node.val <= 104
# 	root is guaranteed to be a valid binary search tree.
# 	-105 <= k <= 105
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def findTarget(self, root, k):
        """
        :type root: Optional[TreeNode]
        :type k: int
        :rtype: bool
        """
        seen = set()
        
        def dfs(node):
            if not node:
                return False
            
            complement = k - node.val
            if complement in seen:
                return True
            
            seen.add(node.val)
            
            return dfs(node.left) or dfs(node.right)
        
        return dfs(root)