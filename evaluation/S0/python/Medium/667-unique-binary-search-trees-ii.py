# Source: https://leetcode.com/problems/unique-binary-search-trees-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return all the structurally unique BST's (binary search trees), which has exactly n nodes of unique values from 1 to n. Return the answer in any order.
#
# Example:
# Input: n = 3
# Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
#
# Constraints:
# 1 <= n <= 8
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def generateTrees(self, n):
        """
        :type n: int
        :rtype: List[Optional[TreeNode]]
        """
        if n == 0:
            return []
        
        def build_trees(start, end):
            if start > end:
                return [None]
            
            all_trees = []
            for i in range(start, end + 1):
                left_trees = build_trees(start, i - 1)
                right_trees = build_trees(i + 1, end)
                
                for l in left_trees:
                    for r in right_trees:
                        current_tree = TreeNode(i)
                        current_tree.left = l
                        current_tree.right = r
                        all_trees.append(current_tree)
            
            return all_trees
        
        return build_trees(1, n)