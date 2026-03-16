# Source: https://leetcode.com/problems/add-two-numbers-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.
#
# You may assume the two numbers do not contain any leading zero, except the number 0 itself.
#
# Example:
# Input: l1 = [7,2,4,3], l2 = [5,6,4]
# Output: [7,8,0,7]
#
# Constraints:
# The number of nodes in each linked list is in the range [1, 100].
# 	0 <= Node.val <= 9
# 	It is guaranteed that the list represents a number that does not have leading zeros.
#
#
#  
# Follow up: Could you solve it without reversing the input lists?
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def addTwoNumbers(self, l1, l2):
        """
        :type l1: Optional[ListNode]
        :type l2: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        stack1 = []
        stack2 = []
        
        while l1:
            stack1.append(l1.val)
            l1 = l1.next
        
        while l2:
            stack2.append(l2.val)
            l2 = l2.next
        
        carry = 0
        prev = None
        
        while stack1 or stack2 or carry:
            val1 = stack1.pop() if stack1 else 0
            val2 = stack2.pop() if stack2 else 0
            
            total = val1 + val2 + carry
            carry = total // 10
            current_node = ListNode(total % 10)
            current_node.next = prev
            prev = current_node
        
        return prev