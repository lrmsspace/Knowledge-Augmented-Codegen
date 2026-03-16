# Source: https://leetcode.com/problems/maximum-depth-of-n-ary-tree/   |   Difficulty: Easy
#
# Problem Description:
# Given a n-ary tree, find its maximum depth.
#
# The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
#
# Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).
#
# Example:
# Input: root = [1,null,3,2,4,null,5,6]
# Output: 3
#
# Constraints:
# The total number of nodes is in the range [0, 104].
# 	The depth of the n-ary tree is less than or equal to 1000.
#

"""
# Definition for a Node.
class Node(object):
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children
"""
            
class Solution(object):
    def maxDepth(self, root):
        """
        :type root: Node
        :rtype: int
        """
        if root is None:
            return 0
        elif not root.children:
            return 1
        else:
            return 1 + max(self.maxDepth(child) for child in root.children)
