# Source: https://leetcode.com/problems/reverse-nodes-in-even-length-groups/   |   Difficulty: Medium
#
# Problem Description:
# You are given the head of a linked list.
#
# The nodes in the linked list are sequentially assigned to non-empty groups whose lengths form the sequence of the natural numbers (1, 2, 3, 4, ...). The length of a group is the number of nodes assigned to it. In other words,
#
#
# 	The 1st node is assigned to the first group.
# 	The 2nd and the 3rd nodes are assigned to the second group.
# 	The 4th, 5th, and 6th nodes are assigned to the third group, and so on.
#
#
# Note that the length of the last group may be less than or equal to 1 + the length of the second to last group.
#
# Reverse the nodes in each group with an even length, and return the head of the modified linked list.
#
# Example:
# Input: head = [5,2,6,3,9,1,7,3,8,4]
# Output: [5,6,2,3,9,1,4,8,3,7]
# Explanation:
# - The length of the first group is 1, which is odd, hence no reversal occurs.
# - The length of the second group is 2, which is even, hence the nodes are reversed.
# - The length of the third group is 3, which is odd, hence no reversal occurs.
# - The length of the last group is 4, which is even, hence the nodes are reversed.
#
# Constraints:
# The number of nodes in the list is in the range [1, 105].
# 	0 <= Node.val <= 105
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
    def reverseEvenLengthGroups(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        dummy = ListNode(0)
        dummy.next = head
        prev_group_end = dummy
        current = head
        group_size = 1

        while current:
            group_start = current
            count = 0
            
            # Count the nodes in the current group
            while current and count < group_size:
                current = current.next
                count += 1
            
            # If the group has an even length, reverse it
            if count % 2 == 0:
                prev_group_end.next = self.reverse(group_start, count)
                prev_group_end = group_start
            else:
                prev_group_end = group_start
            
            group_size += 1
        
        return dummy.next