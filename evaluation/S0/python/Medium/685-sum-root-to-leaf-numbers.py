# Source: https://leetcode.com/problems/sum-root-to-leaf-numbers/   |   Difficulty: Medium
#
# Problem Description:
# You are given the root of a binary tree containing digits from 0 to 9 only.
#
# Each root-to-leaf path in the tree represents a number.
#
#
# 	For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.
#
#
# Return the total sum of all root-to-leaf numbers. Test cases are generated so that the answer will fit in a 32-bit integer.
#
# A leaf node is a node with no children.
#
# Example:
# Input: root = [1,2,3]
# Output: 25
# Explanation:
# The root-to-leaf path 1->2 represents the number 12.
# The root-to-leaf path 1->3 represents the number 13.
# Therefore, sum = 12 + 13 = 25.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 1000].
# 	0 <= Node.val <= 9
# 	The depth of the tree will not exceed 10.
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def sumNumbers(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        def dfs(node, current_number):
            if not node:
                return 0
            
            current_number = current_number * 10 + node.val
            
            # If it's a leaf node, return the current number
            if not node.left and not node.right:
                return current_number
            
            # Recur for left and right subtrees
            left_sum = dfs(node.left, current_number)
            right_sum = dfs(node.right, current_number)
            
            return left_sum + right_sum
        
        return dfs(root, 0)