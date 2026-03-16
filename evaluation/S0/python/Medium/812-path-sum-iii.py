# Source: https://leetcode.com/problems/path-sum-iii/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree and an integer targetSum, return the number of paths where the sum of the values along the path equals targetSum.
#
# The path does not need to start or end at the root or a leaf, but it must go downwards (i.e., traveling only from parent nodes to child nodes).
#
# Example:
# Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
# Output: 3
# Explanation: The paths that sum to 8 are shown.
#
# Constraints:
# The number of nodes in the tree is in the range [0, 1000].
# 	-109 <= Node.val <= 109
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
        :rtype: int
        """
        def dfs(node, curr_path):
            if not node:
                return 0
            
            curr_path.append(node.val)
            path_count = 0
            path_sum = 0
            
            # Check all sub-paths ending at the current node
            for val in reversed(curr_path):
                path_sum += val
                if path_sum == targetSum:
                    path_count += 1
            
            # Explore left and right subtrees
            path_count += dfs(node.left, curr_path)
            path_count += dfs(node.right, curr_path)
            
            # Backtrack: remove the current node from the path
            curr_path.pop()
            return path_count
        
        return dfs(root, [])