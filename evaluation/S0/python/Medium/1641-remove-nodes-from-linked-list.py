# Source: https://leetcode.com/problems/remove-nodes-from-linked-list/   |   Difficulty: Medium
#
# Problem Description:
# You are given the head of a linked list.
#
# Remove every node which has a node with a greater value anywhere to the right side of it.
#
# Return the head of the modified linked list.
#
# Example:
# Input: head = [5,2,13,3,8]
# Output: [13,8]
# Explanation: The nodes that should be removed are 5, 2 and 3.
# - Node 13 is to the right of node 5.
# - Node 13 is to the right of node 2.
# - Node 8 is to the right of node 3.
#
# Constraints:
# The number of the nodes in the given list is in the range [1, 105].
# 	1 <= Node.val <= 105
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def removeNodes(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        # Reverse the linked list
        prev = None
        current = head
        while current:
            next_node = current.next
            current.next = prev
            prev = current
            current = next_node
        reversed_head = prev

        # Remove nodes that have a greater value on the left (originally right)
        max_value = float('-inf')
        dummy = ListNode(0)
        dummy.next = reversed_head
        current = dummy

        while current and current.next:
            if current.next.val >= max_value:
                max_value = current.next.val
                current = current.next
            else:
                current.next = current.next.next

        # Reverse the linked list again to restore original order
        prev = None
        current = dummy.next
        while current:
            next_node = current.next
            current.next = prev
            prev = current
            current = next_node

        return prev