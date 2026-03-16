# Source: https://leetcode.com/problems/maximum-width-of-binary-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, return the maximum width of the given tree.
#
# The maximum width of a tree is the maximum width among all levels.
#
# The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.
#
# It is guaranteed that the answer will in the range of a 32-bit signed integer.
#
# Example:
# Input: root = [1,3,2,5,3,null,9]
# Output: 4
# Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).
#
# Constraints:
# The number of nodes in the tree is in the range [1, 3000].
# 	-100 <= Node.val <= 100
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def widthOfBinaryTree(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        if not root:
            return 0
        
        max_width = 1
        queue = [(root, 1)]  # (node, index)
        
        while queue:
            level_length = len(queue)
            _, first_index = queue[0]  # index of the first node at current level
            for i in range(level_length):
                node, index = queue.pop(0)
                if node.left:
                    queue.append((node.left, 2 * index))
                if node.right:
                    queue.append((node.right, 2 * index + 1))
            # Calculate width using the last node's index and the first node's index
            max_width = max(max_width, index - first_index + 1)
        
        return max_width