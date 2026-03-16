# Source: https://leetcode.com/problems/balance-a-binary-search-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary search tree, return a balanced binary search tree with the same node values. If there is more than one answer, return any of them.
#
# A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.
#
# Example:
# Input: root = [1,null,2,null,3,null,4,null,null]
# Output: [2,1,3,null,null,null,4]
# Explanation: This is not the only correct answer, [3,1,4,null,2] is also correct.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 104].
# 	1 <= Node.val <= 105
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def balanceBST(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: Optional[TreeNode]
        """
        def inorder_traversal(node, nodes):
            if not node:
                return
            inorder_traversal(node.left, nodes)
            nodes.append(node)
            inorder_traversal(node.right, nodes)

        def build_balanced_bst(nodes, left, right):
            if left > right:
                return None
            mid = (left + right) // 2
            root = nodes[mid]
            root.left = build_balanced_bst(nodes, left, mid - 1)
            root.right = build_balanced_bst(nodes, mid + 1, right)
            return root

        nodes = []
        inorder_traversal(root, nodes)
        return build_balanced_bst(nodes, 0, len(nodes) - 1)