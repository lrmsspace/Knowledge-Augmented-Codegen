# Source: https://leetcode.com/problems/swapping-nodes-in-a-linked-list/   |   Difficulty: Medium
#
# Problem Description:
# You are given the head of a linked list, and an integer k.
#
# Return the head of the linked list after swapping the values of the kth node from the beginning and the kth node from the end (the list is 1-indexed).
#
# Example:
# Input: head = [1,2,3,4,5], k = 2
# Output: [1,4,3,2,5]
#
# Constraints:
# The number of nodes in the list is n.
# 	1 <= k <= n <= 105
# 	0 <= Node.val <= 100
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def swapNodes(self, head, k):
        """
        :type head: Optional[ListNode]
        :type k: int
        :rtype: Optional[ListNode]
        """
        first = second = head
        for _ in range(k - 1):
            first = first.next
        temp = first
        while temp.next:
            temp = temp.next
            second = second.next
        first.val, second.val = second.val, first.val
        return head