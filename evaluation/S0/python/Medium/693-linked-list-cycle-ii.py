# Source: https://leetcode.com/problems/linked-list-cycle-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.
#
# There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to (0-indexed). It is -1 if there is no cycle. Note that pos is not passed as a parameter.
#
# Do not modify the linked list.
#
# Example:
# Input: head = [3,2,0,-4], pos = 1
# Output: tail connects to node index 1
# Explanation: There is a cycle in the linked list, where tail connects to the second node.
#
# Constraints:
# The number of the nodes in the list is in the range [0, 104].
# 	-105 <= Node.val <= 105
# 	pos is -1 or a valid index in the linked-list.
#
#
#  
# Follow up: Can you solve it using O(1) (i.e. constant) memory?
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution(object):
    def detectCycle(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        if not head:
            return None
        
        slow = head
        fast = head
        
        # Step 1: Determine if there is a cycle
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            
            if slow == fast:
                break
        else:
            return None  # No cycle
        
        # Step 2: Find the entry point of the cycle
        slow = head
        while slow != fast:
            slow = slow.next
            fast = fast.next
            
        return slow