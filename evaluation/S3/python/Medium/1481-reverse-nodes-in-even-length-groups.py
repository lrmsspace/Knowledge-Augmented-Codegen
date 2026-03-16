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
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
#   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
#   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
#   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
#   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
# - Linked-list implementations of collections (linked-list, queue, simulation)
#   • When to use: Use when frequent insertions or deletions at the beginning or end of a collection are required, or when the collection size is highly dynamic and unpredictable.
#   • Idea: Linked lists implement dynamic collections like queues and stacks by chaining nodes, each holding an item and a reference to the next node. Operations like adding or removing elements at the ends typically achieve O(1) time complexity, while random access is O(N).
#   • Invariants: The `first` pointer always references the head node, or is null if the list is empty.; The `last` pointer always references the tail node, or is null if the list is empty.
#   • Tips: Maintain separate `first` and `last` pointers for O(1) enqueue/dequeue operations.; Keep a `size` counter to provide O(1) size retrieval.
#   • Pitfalls: Forgetting to update `first` or `last` pointers correctly can lead to broken lists or memory leaks.; Null pointer exceptions are common when traversing or modifying an empty or partially traversed list.
# - Linked-list implementations of collections (linked-list, stack, simulation)
#   • When to use: Use when a Last-In, First-Out (LIFO) data structure is required, and dynamic size with efficient O(1) push and pop operations is crucial, especially without a fixed capacity.
#   • Idea: This describes implementing a stack using a singly linked list, where elements are added and removed from the head of the list. Both push and pop operations achieve O(1) time complexity.
#   • Invariants: The 'first' pointer always points to the top element of the stack, or is null if the stack is empty.; Each node's 'next' pointer correctly links to the subsequent element in the stack, maintaining the LIFO order.
#   • Tips: Maintain a 'first' pointer to the head of the linked list, representing the stack's top.; Push operation involves creating a new node, linking it to the current 'first', then updating 'first'.
#   • Pitfalls: Forgetting to handle the empty stack case for pop, leading to `NoSuchElementException`.; Incorrectly updating the 'first' pointer during push or pop, which can break the list structure.
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
            
            # Count the number of nodes in the current group
            while current and count < group_size:
                current = current.next
                count += 1
            
            if count % 2 == 0:  # If the group size is even, reverse the group
                prev_group_end.next = self.reverse(group_start, count)
                prev_group_end = group_start
            else:
                prev_group_end = self.get_group_end(group_start, count)
            
            group_size += 1
        
        return dummy.next