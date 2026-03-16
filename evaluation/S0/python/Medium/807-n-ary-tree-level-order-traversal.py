# Source: https://leetcode.com/problems/n-ary-tree-level-order-traversal/   |   Difficulty: Medium
#
# Problem Description:
# Given an n-ary tree, return the level order traversal of its nodes' values.
#
# Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).
#
# Example:
# Input: root = [1,null,3,2,4,null,5,6]
# Output: [[1],[3,2,4],[5,6]]
#
# Constraints:
# The height of the n-ary tree is less than or equal to 1000
# 	The total number of nodes is between [0, 104]
#

"""
# Definition for a Node.
class Node(object):
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children
"""

class Solution(object):
    def levelOrder(self, root):
        """
        :type root: Node
        :rtype: List[List[int]]
        """
        if not root:        