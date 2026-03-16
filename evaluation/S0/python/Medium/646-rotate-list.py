# Source: https://leetcode.com/problems/rotate-list/   |   Difficulty: Medium
#
# Problem Description:
# Given the head of a linked list, rotate the list to the right by k places.
#
# Example:
# Input: head = [1,2,3,4,5], k = 2
# Output: [4,5,1,2,3]
#
# Constraints:
# The number of nodes in the list is in the range [0, 500].
# 	-100 <= Node.val <= 100
# 	0 <= k <= 2 * 109
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def rotateRight(self, head, k):
        """
        :type head: Optional[ListNode]
        :type k: int
        :rtype: Optional[ListNode]
        """
        if not head or k == 0:
            return head
        
        # Compute the length of the list and make it circular
        old_tail = head
        n = 1
        while old_tail.next:
            old_tail = old_tail.next
            n += 1
        old_tail.next = head  # Make it circular
        
        # Find the new tail : (n - k % n - 1)th node
        # and the new head : (n - k % n)th node
        k = k % n
        new_tail = head
        for _ in range(n - k - 1):
            new_tail = new_tail.next
        new_head = new_tail.next
        
        # Break the circle
        new_tail.next = None
        
        return new_head