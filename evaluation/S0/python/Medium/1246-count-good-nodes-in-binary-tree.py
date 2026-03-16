# Source: https://leetcode.com/problems/count-good-nodes-in-binary-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given a binary tree root, a node X in the tree is named good if in the path from root to X there are no nodes with a value greater than X.
#
# Return the number of good nodes in the binary tree.
#
# Example:
# Input: root = [3,1,4,3,null,1,5]
# Output: 4
# Explanation: Nodes in blue are good.
# Root Node (3) is always a good node.
# Node 4 -> (3,4) is the maximum value in the path starting from the root.
# Node 5 -> (3,4,5) is the maximum value in the path
# Node 3 -> (3,1,3) is the maximum value in the path.
#
# Constraints:
# The number of nodes in the binary tree is in the range [1, 10^5].
# 	Each node's value is between [-10^4, 10^4].
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def goodNodes(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def dfs(node, max_val):
            if not node:
                return 0
            good = 1 if node.val >= max_val else 0
            max_val = max(max_val, node.val)
            good += dfs(node.left, max_val)
            good += dfs(node.right, max_val)
            return good
        
        return dfs(root, root.val)