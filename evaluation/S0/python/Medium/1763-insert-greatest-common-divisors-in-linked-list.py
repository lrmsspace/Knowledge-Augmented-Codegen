# Source: https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/   |   Difficulty: Medium
#
# Problem Description:
# Given the head of a linked list head, in which each node contains an integer value.
#
# Between every pair of adjacent nodes, insert a new node with a value equal to the greatest common divisor of them.
#
# Return the linked list after insertion.
#
# The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.
#
# Example:
# Input: head = [18,6,10,3]
# Output: [18,6,6,2,10,1,3]
# Explanation: The 1st diagram denotes the initial linked list and the 2nd diagram denotes the linked list after inserting the new nodes (nodes in blue are the inserted nodes).
# - We insert the greatest common divisor of 18 and 6 = 6 between the 1st and the 2nd nodes.
# - We insert the greatest common divisor of 6 and 10 = 2 between the 2nd and the 3rd nodes.
# - We insert the greatest common divisor of 10 and 3 = 1 between the 3rd and the 4th nodes.
# There are no more adjacent nodes, so we return the linked list.
#
# Constraints:
# The number of nodes in the list is in the range [1, 5000].
# 	1 <= Node.val <= 1000
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def insertGreatestCommonDivisors(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        import math
        
        if not head:
            return None
        
        current = head
        
        while current and current.next:
            gcd_value = math.gcd(current.val, current.next.val)
            new_node = ListNode(gcd_value)
            new_node.next = current.next
            current.next = new_node
            current = new_node.next
        
        return head