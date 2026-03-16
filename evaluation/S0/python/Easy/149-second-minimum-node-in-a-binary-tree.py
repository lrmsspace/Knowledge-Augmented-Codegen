# Source: https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/   |   Difficulty: Easy
#
# Problem Description:
# Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes. More formally, the property root.val = min(root.left.val, root.right.val) always holds.
#
# Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.
#
# If no such second minimum value exists, output -1 instead.
#
# Example:
# Input: root = [2,2,5,null,null,5,7]
# Output: 5
# Explanation: The smallest value is 2, the second smallest value is 5.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 25].
# 	1 <= Node.val <= 231 - 1
# 	root.val == min(root.left.val, root.right.val) for each internal node of the tree.
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def findSecondMinimumValue(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        if not root:
            return -1
        
        min_val = root.val
        self.second_min = float('inf')
        
        def dfs(node):
            if not node:
                return
            
            if min_val < node.val < self.second_min:
                self.second_min = node.val
            
            dfs(node.left)
            dfs(node.right)
        
        dfs(root)
        
        return self.second_min if self.second_min != float('inf') else -1