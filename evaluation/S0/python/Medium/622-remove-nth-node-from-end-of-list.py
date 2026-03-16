# Source: https://leetcode.com/problems/remove-nth-node-from-end-of-list/   |   Difficulty: Medium
#
# Problem Description:
# Given the head of a linked list, remove the nth node from the end of the list and return its head.
#
# Example:
# Input: head = [1,2,3,4,5], n = 2
# Output: [1,2,3,5]
#
# Constraints:
# The number of nodes in the list is sz.
# 	1 <= sz <= 30
# 	0 <= Node.val <= 100
# 	1 <= n <= sz
#
#
#  
# Follow up: Could you do this in one pass?
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def removeNthFromEnd(self, head, n):
        """
        :type head: Optional[ListNode]
        :type n: int
        :rtype: Optional[ListNode]
        """
        dummy = ListNode(0)
        dummy.next = head
        first = dummy
        second = dummy
        
        # Move first n+1 steps ahead
        for _ in range(n + 1):
            first = first.next
            
        # Move both pointers until first reaches the end
        while first:
            first = first.next
            second = second.next
            
        # Remove the nth node from the end
        second.next = second.next.next
        
        return dummy.next