# Source: https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, return the lowest common ancestor of its deepest leaves.
#
# Recall that:
#
#
# 	The node of a binary tree is a leaf if and only if it has no children
# 	The depth of the root of the tree is 0. if the depth of a node is d, the depth of each of its children is d + 1.
# 	The lowest common ancestor of a set S of nodes, is the node A with the largest depth such that every node in S is in the subtree with root A.
#
# Example:
# Input: root = [3,5,1,6,2,0,8,null,null,7,4]
# Output: [2,7,4]
# Explanation: We return the node with value 2, colored in yellow in the diagram.
# The nodes coloured in blue are the deepest leaf-nodes of the tree.
# Note that nodes 6, 0, and 8 are also leaf nodes, but the depth of them is 2, but the depth of nodes 7 and 4 is 3.
#
# Constraints:
# The number of nodes in the tree will be in the range [1, 1000].
# 	0 <= Node.val <= 1000
# 	The values of the nodes in the tree are unique.
#
#
#  
# Note: This question is the same as 865: https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def lcaDeepestLeaves(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: Optional[TreeNode]
        """
        def helper(node):
            if not node:
                return (0, None)
            
            left_depth, left_lca = helper(node.left)
            right_depth, right_lca = helper(node.right)
            
            if left_depth > right_depth:
                return (left_depth + 1, left_lca)
            elif right_depth > left_depth:
                return (right_depth + 1, right_lca)
            else:
                return (left_depth + 1, node)
        
        return helper(root)[1]