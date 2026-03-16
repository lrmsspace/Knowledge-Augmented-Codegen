# Source: https://leetcode.com/problems/find-duplicate-subtrees/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, return all duplicate subtrees.
#
# For each kind of duplicate subtrees, you only need to return the root node of any one of them.
#
# Two trees are duplicate if they have the same structure with the same node values.
#
# Example:
# Input: root = [1,2,3,4,null,2,4,null,null,4]
# Output: [[2,4],[4]]
#
# Constraints:
# The number of the nodes in the tree will be in the range [1, 5000]
# 	-200 <= Node.val <= 200
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def findDuplicateSubtrees(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[Optional[TreeNode]]
        """
        from collections import defaultdict
        def serialize(node):
            if not node:
                return "#"
            serial = "{},{},{}".format(node.val, serialize(node.left), serialize(node.right))
            count[serial] += 1
            if count[serial] == 2:
                result.append(node)
            return serial

        count = defaultdict(int)
        result = []
        serialize(root)
        return result