# Source: https://leetcode.com/problems/cousins-in-binary-tree/   |   Difficulty: Easy
#
# Problem Description:
# Given the root of a binary tree with unique values and the values of two different nodes of the tree x and y, return true if the nodes corresponding to the values x and y in the tree are cousins, or false otherwise.
#
# Two nodes of a binary tree are cousins if they have the same depth with different parents.
#
# Note that in a binary tree, the root node is at the depth 0, and children of each depth k node are at the depth k + 1.
#
# Example:
# Input: root = [1,2,3,4], x = 4, y = 3
# Output: false
#
# Constraints:
# The number of nodes in the tree is in the range [2, 100].
# 	1 <= Node.val <= 100
# 	Each node has a unique value.
# 	x != y
# 	x and y are exist in the tree.
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def isCousins(self, root, x, y):
        """
        :type root: Optional[TreeNode]
        :type x: int
        :type y: int
        :rtype: bool
        """
        from collections import deque
        
        if not root:
            return False
        
        queue = deque([(root, None)])  # (node, parent)
        
        while queue:
            level_size = len(queue)
            x_parent = None
            y_parent = None
            
            for _ in range(level_size):
                node, parent = queue.popleft()
                
                if node.val == x:
                    x_parent = parent
                if node.val == y:
                    y_parent = parent
                
                if node.left:
                    queue.append((node.left, node))
                if node.right:
                    queue.append((node.right, node))
            
            if x_parent and y_parent:
                return x_parent != y_parent  # Same level but different parents
            if x_parent or y_parent:
                return False  # Found one but not the other
        
        return False