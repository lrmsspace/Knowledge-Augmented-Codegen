# Source: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.
#
# According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”
#
# Example:
# Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
# Output: 6
# Explanation: The LCA of nodes 2 and 8 is 6.
#
# Constraints:
# The number of nodes in the tree is in the range [2, 105].
# 	-109 <= Node.val <= 109
# 	All Node.val are unique.
# 	p != q
# 	p and q will exist in the BST.
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def lowestCommonAncestor(self, root, p, q):
        """
        :type root: TreeNode
        :type p: TreeNode
        :type q: TreeNode
        :rtype: TreeNode
        """
        # 利用二叉搜索树的性质
        # 如果 p 和 q 都小于根节点，则 LCA 在左子树
        # 如果 p 和 q 都大于根节点，则 LCA 在右子树
        # 否则，当前节点即为 LCA
        if p.val < root.val and q.val < root.val:
            return self.lowestCommonAncestor(root.left, p, q)
        elif p.val > root.val and q.val > root.val:
            return self.lowestCommonAncestor(root.right, p, q)
        else:
            return root