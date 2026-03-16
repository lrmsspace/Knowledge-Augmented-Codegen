# Source: https://leetcode.com/problems/binary-tree-pruning/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, return the same tree where every subtree (of the given tree) not containing a 1 has been removed.
#
# A subtree of a node node is node plus every node that is a descendant of node.
#
# Example:
# Input: root = [1,null,0,0,1]
# Output: [1,null,0,null,1]
# Explanation: 
# Only the red nodes satisfy the property "every subtree not containing a 1".
# The diagram on the right represents the answer.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 200].
# 	Node.val is either 0 or 1.
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def pruneTree(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: Optional[TreeNode]
        """
        if not root:
            return None
        
        root.left = self.pruneTree(root.left)
        root.right = self.pruneTree(root.right)
        
        if root.val == 0 and not root.left and not root.right:
            return None
        
        return root