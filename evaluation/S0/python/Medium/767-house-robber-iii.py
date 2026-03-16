# Source: https://leetcode.com/problems/house-robber-iii/   |   Difficulty: Medium
#
# Problem Description:
# The thief has found himself a new place for his thievery again. There is only one entrance to this area, called root.
#
# Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that all houses in this place form a binary tree. It will automatically contact the police if two directly-linked houses were broken into on the same night.
#
# Given the root of the binary tree, return the maximum amount of money the thief can rob without alerting the police.
#
# Example:
# Input: root = [3,2,3,null,3,null,1]
# Output: 7
# Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 104].
# 	0 <= Node.val <= 104
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def rob(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        memo = {}
        
        def helper(node):
            if not node:
                return 0
            if node in memo:
                return memo[node]
            
            # Money when robbing this node
            rob_this = node.val
            if node.left:
                rob_this += helper(node.left.left) + helper(node.left.right)
            if node.right:
                rob_this += helper(node.right.left) + helper(node.right.right)
            
            # Money when not robbing this node
            not_rob_this = helper(node.left) + helper(node.right)
            
            result = max(rob_this, not_rob_this)
            memo[node] = result
            return result
        
        return helper(root)