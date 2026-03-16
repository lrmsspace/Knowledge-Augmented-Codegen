# Source: https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/   |   Difficulty: Medium
#
# Problem Description:
# Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.
#
# After doing so, return the head of the final linked list.  You may return any such answer.
#
#  
# (Note that in the examples below, all sequences are serializations of ListNode objects.)
#
# Example:
# Input: head = [1,2,-3,3,1]
# Output: [3,1]
# Note: The answer [1,2,1] would also be accepted.
#
# Constraints:
# The given linked list will contain between 1 and 1000 nodes.
# 	Each node in the linked list has -1000 <= node.val <= 1000.
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def removeZeroSumSublists(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        dummy = ListNode(0)
        dummy.next = head
        prefix_sum = 0
        sum_to_node = {0: dummy}
        
        current = head
        while current:
            prefix_sum += current.val
            if prefix_sum in sum_to_node:
                prev_node = sum_to_node[prefix_sum]
                node = prev_node.next
                temp_sum = prefix_sum
                
                while node != current:
                    temp_sum += node.val
                    if temp_sum in sum_to_node:
                        del sum_to_node[temp_sum]
                    node = node.next
                
                prev_node.next = current.next
            else:
                sum_to_node[prefix_sum] = current
            
            current = current.next
        
        return dummy.next