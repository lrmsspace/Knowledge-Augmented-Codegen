# Source: https://leetcode.com/problems/merge-nodes-in-between-zeros/   |   Difficulty: Medium
#
# Problem Description:
# You are given the head of a linked list, which contains a series of integers separated by 0's. The beginning and end of the linked list will have Node.val == 0.
#
# For every two consecutive 0's, merge all the nodes lying in between them into a single node whose value is the sum of all the merged nodes. The modified list should not contain any 0's.
#
# Return the head of the modified linked list.
#
# Example:
# Input: head = [0,3,1,0,4,5,2,0]
# Output: [4,11]
# Explanation: 
# The above figure represents the given linked list. The modified list contains
# - The sum of the nodes marked in green: 3 + 1 = 4.
# - The sum of the nodes marked in red: 4 + 5 + 2 = 11.
#
# Constraints:
# The number of nodes in the list is in the range [3, 2 * 105].
# 	0 <= Node.val <= 1000
# 	There are no two consecutive nodes with Node.val == 0.
# 	The beginning and end of the linked list have Node.val == 0.
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def mergeNodes(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        dummy = ListNode(0)
        tail = dummy
        current = head.next
        current_sum = 0
        
        while current:
            if current.val == 0:
                if current_sum > 0:
                    tail.next = ListNode(current_sum)
                    tail = tail.next
                    current_sum = 0
            else:
                current_sum += current.val
            current = current.next
        
        return dummy.next