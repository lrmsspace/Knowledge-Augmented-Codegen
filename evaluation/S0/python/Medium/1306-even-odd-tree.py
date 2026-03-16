# Source: https://leetcode.com/problems/even-odd-tree/   |   Difficulty: Medium
#
# Problem Description:
# A binary tree is named Even-Odd if it meets the following conditions:
#
#
# 	The root of the binary tree is at level index 0, its children are at level index 1, their children are at level index 2, etc.
# 	For every even-indexed level, all nodes at the level have odd integer values in strictly increasing order (from left to right).
# 	For every odd-indexed level, all nodes at the level have even integer values in strictly decreasing order (from left to right).
#
#
# Given the root of a binary tree, return true if the binary tree is Even-Odd, otherwise return false.
#
# Example:
# Input: root = [1,10,4,3,null,7,9,12,8,6,null,null,2]
# Output: true
# Explanation: The node values on each level are:
# Level 0: [1]
# Level 1: [10,4]
# Level 2: [3,7,9]
# Level 3: [12,8,6,2]
# Since levels 0 and 2 are all odd and increasing and levels 1 and 3 are all even and decreasing, the tree is Even-Odd.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 105].
# 	1 <= Node.val <= 106
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def isEvenOddTree(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: bool
        """
        if not root:
            return True
        
        from collections import deque
        queue = deque([root])
        level = 0
        
        while queue:
            level_size = len(queue)
            prev_value = None
            
            for _ in range(level_size):
                node = queue.popleft()
                
                # Check value parity and order based on level
                if level % 2 == 0:  # Even level
                    if node.val % 2 == 0 or (prev_value is not None and node.val <= prev_value):
                        return False
                else:  # Odd level
                    if node.val % 2 != 0 or (prev_value is not None and node.val >= prev_value):
                        return False
                
                prev_value = node.val
                
                # Add child nodes to the queue
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            level += 1
        
        return True