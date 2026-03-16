# Source: https://leetcode.com/problems/swap-nodes-in-pairs/   |   Difficulty: Medium
#
# Problem Description:
# Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)
#
# Example:
# Input: head = [1,2,3,4]
#
# Output: [2,1,4,3]
#
# Explanation:
#
# Constraints:
# The number of nodes in the list is in the range [0, 100].
# 	0 <= Node.val <= 100
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def swapPairs(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        dummy = ListNode(0)
        dummy.next = head
        prev = dummy
        
        while head and head.next:
            first_node = head
            second_node = head.next
            
            # Swapping
            prev.next = second_node
            first_node.next = second_node.next
            second_node.next = first_node
            
            # Reinitializing the pointers for next swap
            prev = first_node
            head = first_node.next
            
        return dummy.next