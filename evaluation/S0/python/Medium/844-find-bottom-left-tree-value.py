# Source: https://leetcode.com/problems/find-bottom-left-tree-value/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, return the leftmost value in the last row of the tree.
#
# Example:
# Input: root = [2,1,3]
# Output: 1
#
# Constraints:
# The number of nodes in the tree is in the range [1, 104].
# 	-231 <= Node.val <= 231 - 1
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def findBottomLeftValue(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        from collections import deque
        
        queue = deque([root])
        leftmost_value = root.val
        
        while queue:
            level_size = len(queue)
            for i in range(level_size):
                node = queue.popleft()
                
                # Update leftmost value at the start of each level
                if i == 0:
                    leftmost_value = node.val
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
        
        return leftmost_value