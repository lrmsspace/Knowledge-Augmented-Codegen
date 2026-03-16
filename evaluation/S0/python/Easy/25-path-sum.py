# Source: https://leetcode.com/problems/path-sum/   |   Difficulty: Easy
#
# Problem Description:
# Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.
#
# A leaf is a node with no children.
#
# Example:
# Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
# Output: true
# Explanation: The root-to-leaf path with the target sum is shown.
#
# Constraints:
# The number of nodes in the tree is in the range [0, 5000].
# 	-1000 <= Node.val <= 1000
# 	-1000 <= targetSum <= 1000
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def hasPathSum(self, root, targetSum):
        """
        :type root: Optional[TreeNode]
        :type targetSum: int
        :rtype: bool
        """
        if not root:
            return False
        
        # If it's a leaf node, check if the remaining targetSum equals the node's value
        if not root.left and not root.right:
            return targetSum == root.val
        
        # Recursively check the left and right subtrees with the updated targetSum
        targetSum -= root.val
        return (self.hasPathSum(root.left, targetSum) or 
                self.hasPathSum(root.right, targetSum))