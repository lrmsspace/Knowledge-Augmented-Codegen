# Source: https://leetcode.com/problems/range-sum-of-bst/   |   Difficulty: Easy
#
# Problem Description:
# Given the root node of a binary search tree and two integers low and high, return the sum of values of all nodes with a value in the inclusive range [low, high].
#
# Example:
# Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
# Output: 32
# Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 2 * 104].
# 	1 <= Node.val <= 105
# 	1 <= low <= high <= 105
# 	All Node.val are unique.
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def rangeSumBST(self, root, low, high):
        """
        :type root: Optional[TreeNode]
        :type low: int
        :type high: int
        :rtype: int
        """
        if not root:
            return 0
        
        total = 0
        
        if low <= root.val <= high:
            total += root.val
        
        if root.val > low:
            total += self.rangeSumBST(root.left, low, high)
        
        if root.val < high:
            total += self.rangeSumBST(root.right, low, high)
        
        return total