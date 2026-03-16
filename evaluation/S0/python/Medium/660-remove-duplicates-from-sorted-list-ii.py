# Source: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list. Return the linked list sorted as well.
#
# Example:
# Input: head = [1,2,3,3,4,4,5]
# Output: [1,2,5]
#
# Constraints:
# The number of nodes in the list is in the range [0, 300].
# 	-100 <= Node.val <= 100
# 	The list is guaranteed to be sorted in ascending order.
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def deleteDuplicates(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        dummy = ListNode(0)
        dummy.next = head
        prev = dummy
        current = head
        
        while current:
            # Check for duplicates
            if current.next and current.val == current.next.val:
                # Skip all nodes with the same value
                while current.next and current.val == current.next.val:
                    current = current.next
                # Link prev to the node after the last duplicate
                prev.next = current.next
            else:
                # No duplicates, move prev pointer
                prev = prev.next
            # Move to the next node
            current = current.next
        
        return dummy.next