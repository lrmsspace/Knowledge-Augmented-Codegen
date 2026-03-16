# Source: https://leetcode.com/problems/reverse-nodes-in-k-group/   |   Difficulty: Hard
#
# Problem Description:
# Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.
#
# k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.
#
# You may not alter the values in the list's nodes, only nodes themselves may be changed.
#
# Example:
# Input: head = [1,2,3,4,5], k = 2
# Output: [2,1,4,3,5]
#
# Constraints:
# The number of nodes in the list is n.
# 	1 <= k <= n <= 5000
# 	0 <= Node.val <= 1000
#
#
#  
# Follow-up: Can you solve the problem in O(1) extra memory space?
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def reverseKGroup(self, head, k):
        """
        :type head: Optional[ListNode]
        :type k: int
        :rtype: Optional[ListNode]
        """
        dummy = ListNode(0)
        dummy.next = head
        prev_group_end = dummy

        while True:
            kth_node = prev_group_end
            for _ in range(k):
                kth_node = kth_node.next
                if not kth_node:
                    return dummy.next

            group_start = prev_group_end.next
            next_group_start = kth_node.next

            # Reverse the k nodes
            prev, curr = None, group_start
            for _ in range(k):
                temp = curr.next
                curr.next = prev
                prev = curr
                curr = temp

            # Connect with the previous part
            prev_group_end.next = kth_node
            group_start.next = next_group_start

            # Move to the next group
            prev_group_end = group_start