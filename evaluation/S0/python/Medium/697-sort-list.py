# Source: https://leetcode.com/problems/sort-list/   |   Difficulty: Medium
#
# Problem Description:
# Given the head of a linked list, return the list after sorting it in ascending order.
#
# Example:
# Input: head = [4,2,1,3]
# Output: [1,2,3,4]
#
# Constraints:
# The number of nodes in the list is in the range [0, 5 * 104].
# 	-105 <= Node.val <= 105
#
#
#  
# Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def sortList(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        if not head or not head.next:
            return head
        
        # Split the list into two halves
        slow, fast = head, head.next
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        
        mid = slow.next
        slow.next = None
        
        # Sort each half
        left = self.sortList(head)
        right = self.sortList(mid)
        
        # Merge the sorted halves
        return self.merge(left, right)