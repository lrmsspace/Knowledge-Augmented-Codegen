# Source: https://leetcode.com/problems/palindrome-linked-list/   |   Difficulty: Easy
#
# Problem Description:
# Given the head of a singly linked list, return true if it is a palindrome or false otherwise.
#
# Example:
# Input: head = [1,2,2,1]
# Output: true
#
# Constraints:
# The number of nodes in the list is in the range [1, 105].
# 	0 <= Node.val <= 9
#
#
#  
# Follow up: Could you do it in O(n) time and O(1) space?
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def isPalindrome(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: bool
        """
        if not head or not head.next:
            return True
        
        # Step 1: Find the end of the first half and reverse the second half.
        def end_of_first_half(node):
            slow = fast = node
            while fast.next and fast.next.next:
                slow = slow.next
                fast = fast.next.next
            return slow
        
        def reverse_list(node):
            prev = None
            current = node
            while current:
                next_node = current.next
                current.next = prev
                prev = current
                current = next_node
            return prev
        
        first_half_end = end_of_first_half(head)
        second_half_start = reverse_list(first_half_end.next)
        
        # Step 2: Check whether or not there is a palindrome.
        p1, p2 = head, second_half_start
        result = True
        while result and p2:
            if p1.val != p2.val:
                result = False
            p1 = p1.next
            p2 = p2.next
        
        # Step 3: Restore the list and return the result.
        first_half_end.next = reverse_list(second_half_start)
        
        return result