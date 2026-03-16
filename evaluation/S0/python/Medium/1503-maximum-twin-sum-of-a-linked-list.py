# Source: https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/   |   Difficulty: Medium
#
# Problem Description:
# In a linked list of size n, where n is even, the ith node (0-indexed) of the linked list is known as the twin of the (n-1-i)th node, if 0 <= i <= (n / 2) - 1.
#
#
# 	For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the twin of node 2. These are the only nodes with twins for n = 4.
#
#
# The twin sum is defined as the sum of a node and its twin.
#
# Given the head of a linked list with even length, return the maximum twin sum of the linked list.
#
# Example:
# Input: head = [5,4,2,1]
# Output: 6
# Explanation:
# Nodes 0 and 1 are the twins of nodes 3 and 2, respectively. All have twin sum = 6.
# There are no other nodes with twins in the linked list.
# Thus, the maximum twin sum of the linked list is 6.
#
# Constraints:
# The number of nodes in the list is an even integer in the range [2, 105].
# 	1 <= Node.val <= 105
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def pairSum(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: int
        """
        vals = []
        node = head
        while node:
            vals.append(node.val)
            node = node.next
        
        max_sum = 0
        n = len(vals)
        for i in range(n // 2):
            twin_sum = vals[i] + vals[n - 1 - i]
            max_sum = max(max_sum, twin_sum)
        
        return max_sum