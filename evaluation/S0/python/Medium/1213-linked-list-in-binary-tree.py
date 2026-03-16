# Source: https://leetcode.com/problems/linked-list-in-binary-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given a binary tree root and a linked list with head as the first node. 
#
# Return True if all the elements in the linked list starting from the head correspond to some downward path connected in the binary tree otherwise return False.
#
# In this context downward path means a path that starts at some node and goes downwards.
#
# Example:
# Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
# Output: true
# Explanation: Nodes in blue form a subpath in the binary Tree.
#
# Constraints:
# The number of nodes in the tree will be in the range [1, 2500].
# 	The number of nodes in the list will be in the range [1, 100].
# 	1 <= Node.val <= 100 for each node in the linked list and binary tree.
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def isSubPath(self, head, root):
        """
        :type head: Optional[ListNode]
        :type root: Optional[TreeNode]
        :rtype: bool
        """
        if not head:
            return True
        if not root:
            return False
        
        def dfs(list_node, tree_node):
            if not list_node:
                return True
            if not tree_node:
                return False
            if list_node.val != tree_node.val:
                return False
            return dfs(list_node.next, tree_node.left) or dfs(list_node.next, tree_node.right)
        
        return (dfs(head, root) or 
                self.isSubPath(head, root.left) or 
                self.isSubPath(head, root.right))