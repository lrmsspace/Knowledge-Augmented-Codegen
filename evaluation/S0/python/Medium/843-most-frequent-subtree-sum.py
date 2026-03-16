# Source: https://leetcode.com/problems/most-frequent-subtree-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.
#
# The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).
#
# Example:
# Input: root = [5,2,-3]
# Output: [2,-3,4]
#
# Constraints:
# The number of nodes in the tree is in the range [1, 104].
# 	-105 <= Node.val <= 105
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def findFrequentTreeSum(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[int]
        """
        if not root:
            return []
        
        from collections import defaultdict
        
        sum_count = defaultdict(int)
        
        def subtree_sum(node):
            if not node:
                return 0
            total = node.val + subtree_sum(node.left) + subtree_sum(node.right)
            sum_count[total] += 1
            return total
        
        subtree_sum(root)
        
        if not sum_count:
            return []
        
        max_freq = max(sum_count.values())
        
        return [s for s, count in sum_count.items() if count == max_freq]