# Source: https://leetcode.com/problems/binary-tree-level-order-traversal-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values. (i.e., from left to right, level by level from leaf to root).
#
# Example:
# Input: root = [3,9,20,null,null,15,7]
# Output: [[15,7],[9,20],[3]]
#
# Constraints:
# The number of nodes in the tree is in the range [0, 2000].
# 	-1000 <= Node.val <= 1000
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def levelOrderBottom(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[List[int]]
        """
        if not root:
            return []
        
        from collections import deque
        
        result = []
        queue = deque([root])
        
        while queue:
            level_size = len(queue)
            current_level = []
            
            for _ in range(level_size):
                node = queue.popleft()
                current_level.append(node.val)
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            result.insert(0, current_level)  # Insert at the beginning for bottom-up order
        
        return result