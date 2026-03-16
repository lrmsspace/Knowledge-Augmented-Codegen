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
        vals = []
        current = head
        while current:
            vals.append(current.val)
            current = current.next
        
        left, right = 0, len(vals) - 1
        while left < right:
            if vals[left] != vals[right]:
                return False
            left += 1
            right -= 1
        
        return True