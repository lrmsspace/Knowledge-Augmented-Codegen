# Source: https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given the head of a singly linked list where elements are sorted in ascending order, convert it to a height-balanced binary search tree.
#
# Example:
# Input: head = [-10,-3,0,5,9]
# Output: [0,-3,9,-10,null,5]
# Explanation: One possible answer is [0,-3,9,-10,null,5], which represents the shown height balanced BST.
#
# Constraints:
# The number of nodes in head is in the range [0, 2 * 104].
# 	-105 <= Node.val <= 105
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
    def sortedListToBST(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: Optional[TreeNode]
        """
        def find_size(head):
            ptr = head
            c = 0
            while ptr:
                ptr = ptr.next
                c += 1
            return c

        size = find_size(head)
        self.current_node = head

        def convert_list_to_bst(left, right):
            if left > right:
                return None

            mid = (left + right) // 2

            left_child = convert_list_to_bst(left, mid - 1)

            node = TreeNode(self.current_node.val)
            node.left = left_child

            self.current_node = self.current_node.next

            node.right = convert_list_to_bst(mid + 1, right)
            return node

        return convert_list_to_bst(0, size - 1)