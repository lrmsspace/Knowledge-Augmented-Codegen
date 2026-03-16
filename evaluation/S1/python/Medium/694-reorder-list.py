# Source: https://leetcode.com/problems/reorder-list/   |   Difficulty: Medium
#
# Problem Description:
# You are given the head of a singly linked-list. The list can be represented as:
#
#
# L0 → L1 → … → Ln - 1 → Ln
#
#
# Reorder the list to be on the following form:
#
#
# L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
#
#
# You may not modify the values in the list's nodes. Only nodes themselves may be changed.
#
# Example:
# Input: head = [1,2,3,4]
# Output: [1,4,2,3]
#
# Constraints:
# The number of nodes in the list is in the range [1, 5 * 104].
# 	1 <= Node.val <= 1000
#
# Helpful references (internal KB):
# - Linked-list implementations of collections (linked-list, queue, simulation)
#   • When to use: Use when frequent insertions or deletions at the beginning or end of a collection are required, or when the collection size is highly dynamic and unpredictable.
#   • Idea: Linked lists implement dynamic collections like queues and stacks by chaining nodes, each holding an item and a reference to the next node. Operations like adding or removing elements at the ends typically achieve O(1) time complexity, while random access is O(N).
#   • Invariants: The `first` pointer always references the head node, or is null if the list is empty.; The `last` pointer always references the tail node, or is null if the list is empty.
#   • Tips: Maintain separate `first` and `last` pointers for O(1) enqueue/dequeue operations.; Keep a `size` counter to provide O(1) size retrieval.
#   • Pitfalls: Forgetting to update `first` or `last` pointers correctly can lead to broken lists or memory leaks.; Null pointer exceptions are common when traversing or modifying an empty or partially traversed list.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
#   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
#   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
#   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
#   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
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
    def reorderList(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: None Do not return anything, modify head in-place instead.
        """
        if not head or not head.next:
            return
        
        # Step 1: Find the middle of the linked list
        slow, fast = head, head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        
        # Step 2: Reverse the second half of the list
        prev, curr = None, slow
        while curr:
            next_temp = curr.next
            curr.next = prev
            prev = curr
            curr = next_temp
        
        # Step 3: Merge the two halves
        first, second = head, prev
        while second.next:
            temp1, temp2 = first.next, second.next
            first.next = second
            second.next = temp1
            first, second = temp1, temp2