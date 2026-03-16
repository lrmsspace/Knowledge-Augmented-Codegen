# Source: https://leetcode.com/problems/find-largest-value-in-each-tree-row/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, return an array of the largest value in each row of the tree (0-indexed).
#
# Example:
# Input: root = [1,3,2,5,3,null,9]
# Output: [1,3,9]
#
# Constraints:
# The number of nodes in the tree will be in the range [0, 104].
# 	-231 <= Node.val <= 231 - 1
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def largestValues(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[int]
        """
        if not root:
            return []
        
        from collections import deque
        queue = deque([root])
        result = []
        
        while queue:
            level_size = len(queue)
            max_value = float('-inf')
            
            for _ in range(level_size):
                node = queue.popleft()
                max_value = max(max_value, node.val)
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            result.append(max_value)
        
        return result