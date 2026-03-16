# Source: https://leetcode.com/problems/all-possible-full-binary-trees/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return a list of all possible full binary trees with n nodes. Each node of each tree in the answer must have Node.val == 0.
#
# Each element of the answer is the root node of one possible tree. You may return the final list of trees in any order.
#
# A full binary tree is a binary tree where each node has exactly 0 or 2 children.
#
# Example:
# Input: n = 7
# Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
#
# Constraints:
# 1 <= n <= 20
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def allPossibleFBT(self, n):
        """
        :type n: int
        :rtype: List[Optional[TreeNode]]
        """
        if n % 2 == 0:
            return []
        
        memo = {}

        def build_trees(nodes):
            if nodes in memo:
                return memo[nodes]
            
            if nodes == 1:
                return [TreeNode(0)]
            
            result = []
            for left_nodes in range(1, nodes, 2):
                right_nodes = nodes - 1 - left_nodes
                left_trees = build_trees(left_nodes)
                right_trees = build_trees(right_nodes)
                
                for left in left_trees:
                    for right in right_trees:
                        root = TreeNode(0)
                        root.left = left
                        root.right = right
                        result.append(root)
            
            memo[nodes] = result
            return result
        
        return build_trees(n)