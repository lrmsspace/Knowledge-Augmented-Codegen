# Source: https://leetcode.com/problems/next-greater-node-in-linked-list/   |   Difficulty: Medium
#
# Problem Description:
# You are given the head of a linked list with n nodes.
#
# For each node in the list, find the value of the next greater node. That is, for each node, find the value of the first node that is next to it and has a strictly larger value than it.
#
# Return an integer array answer where answer[i] is the value of the next greater node of the ith node (1-indexed). If the ith node does not have a next greater node, set answer[i] = 0.
#
# Example:
# Input: head = [2,1,5]
# Output: [5,5,0]
#
# Constraints:
# The number of nodes in the list is n.
# 	1 <= n <= 104
# 	1 <= Node.val <= 109
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def nextLargerNodes(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: List[int]
        """
        values = []
        current = head
        while current:
            values.append(current.val)
            current = current.next
        
        result = [0] * len(values)
        stack = []
        
        for i in range(len(values)):
            while stack and values[i] > values[stack[-1]]:
                index = stack.pop()
                result[index] = values[i]
            stack.append(i)
        
        return result