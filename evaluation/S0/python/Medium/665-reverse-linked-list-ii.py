# Source: https://leetcode.com/problems/reverse-linked-list-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.
#
# Example:
# Input: head = [1,2,3,4,5], left = 2, right = 4
# Output: [1,4,3,2,5]
#
# Constraints:
# The number of nodes in the list is n.
# 	1 <= n <= 500
# 	-500 <= Node.val <= 500
# 	1 <= left <= right <= n
#
#
#  
# Follow up: Could you do it in one pass?
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def reverseBetween(self, head, left, right):
        """
        :type head: Optional[ListNode]
        :type left: int
        :type right: int
        :rtype: Optional[ListNode]
        """
        if not head or left == right:
            return head

        dummy = ListNode(0)
        dummy.next = head
        prev = dummy

        # Move `prev` to the node before the `left` position
        for _ in range(left - 1):
            prev = prev.next

        # Start reversing the sublist
        reverse_start = prev.next
        curr = reverse_start.next

        for _ in range(right - left):
            reverse_start.next = curr.next
            curr.next = prev.next
            prev.next = curr
            curr = reverse_start.next

        return dummy.next