# Source: https://leetcode.com/problems/reverse-linked-list/   |   Difficulty: Easy
#
# Problem Description:
# Given the head of a singly linked list, reverse the list, and return the reversed list.
#
# Example:
# Input: head = [1,2,3,4,5]
# Output: [5,4,3,2,1]
#
# Constraints:
# The number of nodes in the list is the range [0, 5000].
# 	-5000 <= Node.val <= 5000
#
#
#  
# Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def reverseList(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        prev = None
        curr = head
        
        while curr:
            next_temp = curr.next
            curr.next = prev
            prev = curr
            curr = next_temp
            
        return prev