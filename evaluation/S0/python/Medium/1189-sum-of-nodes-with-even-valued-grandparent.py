# Source: https://leetcode.com/problems/sum-of-nodes-with-even-valued-grandparent/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, return the sum of values of nodes with an even-valued grandparent. If there are no nodes with an even-valued grandparent, return 0.
#
# A grandparent of a node is the parent of its parent if it exists.
#
# Example:
# Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
# Output: 18
# Explanation: The red nodes are the nodes with even-value grandparent while the blue nodes are the even-value grandparents.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 104].
# 	1 <= Node.val <= 100
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def sumEvenGrandparent(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        def dfs(node, parent_val, grandparent_val):
            if not node:
                return 0
            
            total = 0
            if grandparent_val % 2 == 0:
                total += node.val
            
            total += dfs(node.left, node.val, parent_val)
            total += dfs(node.right, node.val, parent_val)
            
            return total
        
        return dfs(root, 1, 1)