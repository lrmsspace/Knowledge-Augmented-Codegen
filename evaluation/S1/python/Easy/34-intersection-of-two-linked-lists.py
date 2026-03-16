# Source: https://leetcode.com/problems/intersection-of-two-linked-lists/   |   Difficulty: Easy
#
# Problem Description:
# Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect. If the two linked lists have no intersection at all, return null.
#
# For example, the following two linked lists begin to intersect at node c1:
#
# The test cases are generated such that there are no cycles anywhere in the entire linked structure.
#
# Note that the linked lists must retain their original structure after the function returns.
#
# Custom Judge:
#
# The inputs to the judge are given as follows (your program is not given these inputs):
#
#
# 	intersectVal - The value of the node where the intersection occurs. This is 0 if there is no intersected node.
# 	listA - The first linked list.
# 	listB - The second linked list.
# 	skipA - The number of nodes to skip ahead in listA (starting from the head) to get to the intersected node.
# 	skipB - The number of nodes to skip ahead in listB (starting from the head) to get to the intersected node.
#
#
# The judge will then create the linked structure based on these inputs and pass the two heads, headA and headB to your program. If you correctly return the intersected node, then your solution will be accepted.
#
# Example:
# Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
# Output: Intersected at '8'
# Explanation: The intersected node's value is 8 (note that this must not be 0 if the two lists intersect).
# From the head of A, it reads as [4,1,8,4,5]. From the head of B, it reads as [5,6,1,8,4,5]. There are 2 nodes before the intersected node in A; There are 3 nodes before the intersected node in B.
# - Note that the intersected node's value is not 1 because the nodes with value 1 in A and B (2nd node in A and 3rd node in B) are different node references. In other words, they point to two different locations in memory, while the nodes with value 8 in A and B (3rd node in A and 4th node in B) point to the same location in memory.
#
# Constraints:
# The number of nodes of listA is in the m.
# 	The number of nodes of listB is in the n.
# 	1 <= m, n <= 3 * 104
# 	1 <= Node.val <= 105
# 	0 <= skipA <= m
# 	0 <= skipB <= n
# 	intersectVal is 0 if listA and listB do not intersect.
# 	intersectVal == listA[skipA] == listB[skipB] if listA and listB intersect.
#
#
#  
# Follow up: Could you write a solution that runs in O(m + n) time and use only O(1) memory?
#
# Helpful references (internal KB):
# - Floyd's Linked List Cycle Finding Algorithm (linked-list, two-pointers, simulation)
#   • When to use: Use this algorithm to efficiently detect if a linked list contains a cycle and, optionally, find the entry point of that cycle, using only constant extra space.
#   • Idea: This algorithm uses two pointers, one moving faster than the other, to detect if a cycle exists in a linked list. If a cycle is found, it can then determine the cycle's starting node in O(N) time complexity and O(1) space complexity.
#   • Invariants: The slow and fast pointers are always valid nodes or null.; In the detection phase, the fast pointer always covers twice the distance of the slow pointer.
#   • Tips: Initialize both slow and fast pointers at the head of the list.; Move the slow pointer by one step and the fast pointer by two steps in each iteration.
#   • Pitfalls: Forgetting to check for null on 'fast' and 'fast.next' before dereferencing them.; Incorrectly assuming the list is non-empty or has at least two nodes.
# - Linked-list implementations of collections (linked-list, ds, simulation)
#   • When to use: When you need dynamic collections that efficiently support insertions and deletions at specific points, or when memory usage needs to be precisely managed without contiguous memory allocation.
#   • Idea: This describes how fundamental data structures like stacks, queues, and bags can be implemented using linked lists, providing dynamic resizing and efficient element manipulation. Operations typically achieve O(1) time complexity for additions and removals at the ends.
#   • Invariants: The head pointer always points to the first element, or is null if the list is empty.; The tail pointer always points to the last element, or is null if the list is empty.
#   • Tips: Use a Node class to encapsulate data and a reference to the next element.; Maintain head and tail pointers for efficient O(1) operations in queues.
#   • Pitfalls: Forgetting to handle edge cases like empty lists or single-element lists.; Introducing 'loitering' by not nullifying references to removed objects, preventing garbage collection.
# - Finding common tangents to two circles (geometry, number, enumeration, simulation)
#   • When to use: Use this when you need to find all lines that are simultaneously tangent to two given circles. It is applicable in computational geometry problems requiring the precise relative positioning of circles and lines.
#   • Idea: This algorithm systematically determines the equations of all common tangent lines to two circles, typically identifying up to four distinct lines. It involves geometric calculations based on circle centers and radii, operating in constant time, O(1).
#   • Invariants: The distance between the two circle centers remains constant.; The radii of both circles are immutable during the tangent calculation.
#   • Tips: Separate calculations for external and internal tangents.; Carefully consider the relative positions of circle centers and radii.
#   • Pitfalls: Overlooking degenerate cases like coincident or concentric circles.; Numerical instability or precision errors with floating-point arithmetic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution(object):
    def getIntersectionNode(self, headA, headB):
        """
        :type head1, head1: ListNode
        :rtype: ListNode
        """
        if not headA or not headB:
            return None
        
        pointerA, pointerB = headA, headB
        
        while pointerA != pointerB:
            pointerA = pointerA.next if pointerA else headB
            pointerB = pointerB.next if pointerB else headA
        
        return pointerA