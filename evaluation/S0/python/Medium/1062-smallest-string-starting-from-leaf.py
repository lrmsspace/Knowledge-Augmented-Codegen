# Source: https://leetcode.com/problems/smallest-string-starting-from-leaf/   |   Difficulty: Medium
#
# Problem Description:
# You are given the root of a binary tree where each node has a value in the range [0, 25] representing the letters 'a' to 'z'.
#
# Return the lexicographically smallest string that starts at a leaf of this tree and ends at the root.
#
# As a reminder, any shorter prefix of a string is lexicographically smaller.
#
#
# 	For example, "ab" is lexicographically smaller than "aba".
#
#
# A leaf of a node is a node that has no children.
#
# Example:
# Input: root = [0,1,2,3,4,3,4]
# Output: "dba"
#
# Constraints:
# The number of nodes in the tree is in the range [1, 8500].
# 	0 <= Node.val <= 25
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def smallestFromLeaf(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: str
        """
        res = "~"
        
        def dfs(node, path):
            nonlocal res
            if not node:
                return
            path.append(chr(node.val + ord('a')))
            if not node.left and not node.right:
                candidate = "".join(reversed(path))
                if candidate < res:
                    res = candidate
            dfs(node.left, path)
            dfs(node.right, path)
            path.pop()
        
        dfs(root, [])
        return res