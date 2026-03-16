# Source: https://leetcode.com/problems/merge-in-between-linked-lists/   |   Difficulty: Medium
#
# Problem Description:
# You are given two linked lists: list1 and list2 of sizes n and m respectively.
#
# Remove list1's nodes from the ath node to the bth node, and put list2 in their place.
#
# The blue edges and nodes in the following figure indicate the result:
#
# Build the result list and return its head.
#
# Example:
# Input: list1 = [10,1,13,6,9,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
# Output: [10,1,13,1000000,1000001,1000002,5]
# Explanation: We remove the nodes 3 and 4 and put the entire list2 in their place. The blue edges and nodes in the above figure indicate the result.
#
# Constraints:
# 3 <= list1.length <= 104
# 	1 <= a <= b < list1.length - 1
# 	1 <= list2.length <= 104
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def mergeInBetween(self, list1, a, b, list2):
        """
        :type list1: ListNode
        :type a: int
        :type b: int
        :type list2: ListNode
        :rtype: ListNode
        """
        dummy = ListNode(0)
        dummy.next = list1
        prev = dummy
        
        # Move prev to the node before position a
        for _ in range(a):
            prev = prev.next
        
        # Move curr to the node at position b
        curr = prev
        for _ in range(b - a + 1):
            curr = curr.next
        
        # Connect prev to list2
        prev.next = list2
        
        # Find the tail of list2
        tail = list2
        while tail.next:
            tail = tail.next
        
        # Connect tail of list2 to curr
        tail.next = curr
        
        return dummy.next