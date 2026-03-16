# Source: https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given a binary tree where node values are digits from 1 to 9. A path in the binary tree is said to be pseudo-palindromic if at least one permutation of the node values in the path is a palindrome.
#
# Return the number of pseudo-palindromic paths going from the root node to leaf nodes.
#
# Example:
# Input: root = [2,3,1,3,1,null,1]
# Output: 2 
# Explanation: The figure above represents the given binary tree. There are three paths going from the root node to leaf nodes: the red path [2,3,3], the green path [2,1,1], and the path [2,3,1]. Among these paths only red path and green path are pseudo-palindromic paths since the red path [2,3,3] can be rearranged in [3,2,3] (palindrome) and the green path [2,1,1] can be rearranged in [1,2,1] (palindrome).
#
# Constraints:
# The number of nodes in the tree is in the range [1, 105].
# 	1 <= Node.val <= 9
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def pseudoPalindromicPaths (self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        def dfs(node, count):
            if not node:
                return 0
            
            # Update the count of the current node's value
            count[node.val] += 1
            
            # If it's a leaf node, check if the path is pseudo-palindromic
            if not node.left and not node.right:
                odd_count = sum(1 for v in count.values() if v % 2 != 0)
                return 1 if odd_count <= 1 else 0
            
            # Continue DFS on left and right children
            left_paths = dfs(node.left, count)
            right_paths = dfs(node.right, count)
            
            # Backtrack: remove the current node's value from the count
            count[node.val] -= 1
            
            return left_paths + right_paths
        
        from collections import defaultdict
        return dfs(root, defaultdict(int))