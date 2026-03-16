# Source: https://leetcode.com/problems/n-ary-tree-postorder-traversal/   |   Difficulty: Easy
#
# Problem Description:
# Given the root of an n-ary tree, return the postorder traversal of its nodes' values.
#
# Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)
#
# Example:
# Input: root = [1,null,3,2,4,null,5,6]
# Output: [5,6,3,2,4,1]
#
# Constraints:
# The number of nodes in the tree is in the range [0, 104].
# 	0 <= Node.val <= 104
# 	The height of the n-ary tree is less than or equal to 1000.
#
#
#  
# Follow up: Recursive solution is trivial, could you do it iteratively?
#

"""
# Definition for a Node.
class Node(object):
	def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        self.val = val
        self.children = children
"""

class Solution(object):
    def postorder(self, root):
        """
        :type root: Node
        :rtype: List[int]
        """
        result = []     
        if root is None:
            return result
        stack = [root]
        while stack:
            node = stack.pop()
            result.append(node.val)
            for child in node.children:
                stack.append(child)
        return result[::-1]