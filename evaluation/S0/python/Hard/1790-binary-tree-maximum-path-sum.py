# Source: https://leetcode.com/problems/binary-tree-maximum-path-sum/   |   Difficulty: Hard
#
# Problem Description:
# A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.
#
# The path sum of a path is the sum of the node's values in the path.
#
# Given the root of a binary tree, return the maximum path sum of any non-empty path.
#
# Example:
# Input: root = [1,2,3]
# Output: 6
# Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 3 * 104].
# 	-1000 <= Node.val <= 1000
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def maxPathSum(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        self.max_sum = float('-inf')

        def helper(node):
            if not node:
                return 0

            left_gain = max(helper(node.left), 0)
            right_gain = max(helper(node.right), 0)

            current_path_sum = node.val + left_gain + right_gain
            self.max_sum = max(self.max_sum, current_path_sum)

            return node.val + max(left_gain, right_gain)

        helper(root)
        return self.max_sum