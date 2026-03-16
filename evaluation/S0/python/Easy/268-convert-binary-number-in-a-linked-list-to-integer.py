# Source: https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/   |   Difficulty: Easy
#
# Problem Description:
# Given head which is a reference node to a singly-linked list. The value of each node in the linked list is either 0 or 1. The linked list holds the binary representation of a number.
#
# Return the decimal value of the number in the linked list.
#
# The most significant bit is at the head of the linked list.
#
# Example:
# Input: head = [1,0,1]
# Output: 5
# Explanation: (101) in base 2 = (5) in base 10
#
# Constraints:
# The Linked List is not empty.
# 	Number of nodes will not exceed 30.
# 	Each node's value is either 0 or 1.
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def getDecimalValue(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: int
        """
        num = 0
        while head:
            num = (num << 1) | head.val
            head = head.next
        return num