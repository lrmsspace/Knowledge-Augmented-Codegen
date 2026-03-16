# Source: https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/   |   Difficulty: Medium
#
# Problem Description:
# You are given the head of a non-empty linked list representing a non-negative integer without leading zeroes.
#
# Return the head of the linked list after doubling it.
#
# Example:
# Input: head = [1,8,9]
# Output: [3,7,8]
# Explanation: The figure above corresponds to the given linked list which represents the number 189. Hence, the returned linked list represents the number 189 * 2 = 378.
#
# Constraints:
# The number of nodes in the list is in the range [1, 104]
# 	0 <= Node.val <= 9
# 	The input is generated such that the list represents a number that does not have leading zeros, except the number 0 itself.
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def doubleIt(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        # Convert linked list to number
        num = 0
        current = head
        while current:
            num = num * 10 + current.val
            current = current.next
        
        # Double the number
        num *= 2
        
        # Convert number back to linked list
        dummy = ListNode(0)
        current = dummy
        for digit in str(num):
            current.next = ListNode(int(digit))
            current = current.next
        
        return dummy.next