# Source: https://leetcode.com/problems/average-of-levels-in-binary-tree/   |   Difficulty: Easy
#
# Problem Description:
# Given the root of a binary tree, return the average value of the nodes on each level in the form of an array. Answers within 10-5 of the actual answer will be accepted.
#
# Example:
# Input: root = [3,9,20,null,null,15,7]
# Output: [3.00000,14.50000,11.00000]
# Explanation: The average value of nodes on level 0 is 3, on level 1 is 14.5, and on level 2 is 11.
# Hence return [3, 14.5, 11].
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
    def averageOfLevels(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[float]
        """
        if not root:
            return []
        
        from collections import deque
        
        result = []
        queue = deque([root])
        
        while queue:
            level_sum = 0
            level_count = len(queue)
            
            for _ in range(level_count):
                node = queue.popleft()
                level_sum += node.val
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            average = level_sum / level_count
            result.append(average)
        
        return result