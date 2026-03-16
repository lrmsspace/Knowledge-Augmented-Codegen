# Source: https://leetcode.com/problems/deepest-leaves-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, return the sum of values of its deepest leaves.
#
# Example:
# Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
# Output: 15
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
    def deepestLeavesSum(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        if not root:
            return 0
        
        from collections import deque
        
        queue = deque([root])
        deepest_sum = 0
        
        while queue:
            level_size = len(queue)
            deepest_sum = 0  # Reset sum for the current level
            
            for _ in range(level_size):
                node = queue.popleft()
                deepest_sum += node.val
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
        
        return deepest_sum