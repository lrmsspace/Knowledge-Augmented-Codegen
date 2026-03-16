# Source: https://leetcode.com/problems/path-sum-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths where the sum of the node values in the path equals targetSum. Each path should be returned as a list of the node values, not node references.
#
# A root-to-leaf path is a path starting from the root and ending at any leaf node. A leaf is a node with no children.
#
# Example:
# Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
# Output: [[5,4,11,2],[5,8,4,5]]
# Explanation: There are two paths whose sum equals targetSum:
# 5 + 4 + 11 + 2 = 22
# 5 + 8 + 4 + 5 = 22
#
# Constraints:
# The number of nodes in the tree is in the range [0, 5000].
# 	-1000 <= Node.val <= 1000
# 	-1000 <= targetSum <= 1000
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def pathSum(self, root, targetSum):
        """
        :type root: Optional[TreeNode]
        :type targetSum: int
        :rtype: List[List[int]]
        """
        res = []
        
        def dfs(node, current_path, current_sum):
            if not node:
                return
            
            current_path.append(node.val)
            current_sum += node.val
            
            if not node.left and not node.right:  # Leaf node
                if current_sum == targetSum:
                    res.append(list(current_path))
            else:
                dfs(node.left, current_path, current_sum)
                dfs(node.right, current_path, current_sum)
            
            current_path.pop()  # Backtrack
        
        dfs(root, [], 0)
        return res