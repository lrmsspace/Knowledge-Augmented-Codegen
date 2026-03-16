# Source: https://leetcode.com/problems/binary-tree-paths/   |   Difficulty: Easy
#
# Problem Description:
# Given the root of a binary tree, return all root-to-leaf paths in any order.
#
# A leaf is a node with no children.
#
# Example:
# Input: root = [1,2,3,null,5]
# Output: ["1->2->5","1->3"]
#
# Constraints:
# The number of nodes in the tree is in the range [1, 100].
# 	-100 <= Node.val <= 100
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def binaryTreePaths(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[str]
        """
        if not root:
            return []
        
        paths = []
        
        def construct_paths(node, path):
            if node:
                path += str(node.val)
                if not node.left and not node.right:  # if leaf node
                    paths.append(path)  # add path to paths
                else:
                    path += "->"  # extend the current path
                    construct_paths(node.left, path)
                    construct_paths(node.right, path)
        
        construct_paths(root, "")
        return paths