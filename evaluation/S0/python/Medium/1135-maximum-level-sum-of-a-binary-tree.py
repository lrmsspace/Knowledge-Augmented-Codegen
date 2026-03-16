# Source: https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.
#
# Return the smallest level x such that the sum of all the values of nodes at level x is maximal.
#
# Example:
# Input: root = [1,7,0,7,-8,null,null]
# Output: 2
# Explanation: 
# Level 1 sum = 1.
# Level 2 sum = 7 + 0 = 7.
# Level 3 sum = 7 + -8 = -1.
# So we return the level with the maximum sum which is level 2.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 104].
# 	-105 <= Node.val <= 105
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def maxLevelSum(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        if not root:
            return 0
        
        from collections import deque, defaultdict
        
        queue = deque([root])
        level = 1
        max_sum = float('-inf')
        result_level = 1
        
        while queue:
            level_size = len(queue)
            current_level_sum = 0
            
            for _ in range(level_size):
                node = queue.popleft()
                current_level_sum += node.val
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            if current_level_sum > max_sum:
                max_sum = current_level_sum
                result_level = level
            
            level += 1
        
        return result_level