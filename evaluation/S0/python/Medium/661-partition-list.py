# Source: https://leetcode.com/problems/partition-list/   |   Difficulty: Medium
#
# Problem Description:
# Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
#
# You should preserve the original relative order of the nodes in each of the two partitions.
#
# Example:
# Input: head = [1,4,3,2,5,2], x = 3
# Output: [1,2,2,4,3,5]
#
# Constraints:
# The number of nodes in the list is in the range [0, 200].
# 	-100 <= Node.val <= 100
# 	-200 <= x <= 200
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def partition(self, head, x):
        """
        :type head: Optional[ListNode]
        :type x: int
        :rtype: Optional[ListNode]
        """
        before_head = ListNode(0)
        before = before_head
        after_head = ListNode(0)
        after = after_head
        
        while head:
            if head.val < x:
                before.next = head
                before = before.next
            else:
                after.next = head
                after = after.next
            head = head.next
        
        after.next = None
        before.next = after_head.next
        
        return before_head.next