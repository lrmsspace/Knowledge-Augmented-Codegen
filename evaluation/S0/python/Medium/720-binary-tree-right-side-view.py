# Source: https://leetcode.com/problems/binary-tree-right-side-view/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.
#
# Example:
# Input: root = [1,2,3,null,5,null,4]
#
# Output: [1,3,4]
#
# Explanation:
#
# Constraints:
# The number of nodes in the tree is in the range [0, 100].
# 	-100 <= Node.val <= 100
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def rightSideView(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[int]
        """
        if not root:
            return []
        
        from collections import deque
        
        queue = deque([root])
        rightside = []
        
        while queue:
            level_length = len(queue)
            for i in range(level_length):
                node = queue.popleft()
                
                # If it's the last node in the current level, add it to the rightside view
                if i == level_length - 1:
                    rightside.append(node.val)
                
                # Add child nodes to the queue
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
        
        return rightside