# Source: https://leetcode.com/problems/cousins-in-binary-tree-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, replace the value of each node in the tree with the sum of all its cousins' values.
#
# Two nodes of a binary tree are cousins if they have the same depth with different parents.
#
# Return the root of the modified tree.
#
# Note that the depth of a node is the number of edges in the path from the root node to it.
#
# Example:
# Input: root = [5,4,9,1,10,null,7]
# Output: [0,0,0,7,7,null,11]
# Explanation: The diagram above shows the initial binary tree and the binary tree after changing the value of each node.
# - Node with value 5 does not have any cousins so its sum is 0.
# - Node with value 4 does not have any cousins so its sum is 0.
# - Node with value 9 does not have any cousins so its sum is 0.
# - Node with value 1 has a cousin with value 7 so its sum is 7.
# - Node with value 10 has a cousin with value 7 so its sum is 7.
# - Node with value 7 has cousins with values 1 and 10 so its sum is 11.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 105].
# 	1 <= Node.val <= 104
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def replaceValueInTree(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: Optional[TreeNode]
        """
        if not root:
            return None
        
        from collections import deque, defaultdict
        
        queue = deque([root])
        level_sum = defaultdict(int)
        parent_sum = defaultdict(int)
        
        level = 0
        while queue:
            level_size = len(queue)
            current_level_sum = 0
            
            for _ in range(level_size):
                node = queue.popleft()
                current_level_sum += node.val
                
                if node.left:
                    queue.append(node.left)
                    parent_sum[node.left] = node.val
                if node.right:
                    queue.append(node.right)
                    parent_sum[node.right] = node.val
            
            level_sum[level] = current_level_sum
            level += 1
        
        queue = deque([root])
        level = 0
        
        while queue:
            level_size = len(queue)
            
            for _ in range(level_size):
                node = queue.popleft()
                
                cousin_sum = level_sum[level] - parent_sum[node]
                node.val = cousin_sum
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            level += 1
        
        return root