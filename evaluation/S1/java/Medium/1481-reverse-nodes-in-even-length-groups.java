// Source: https://leetcode.com/problems/reverse-nodes-in-even-length-groups/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list.
//
// The nodes in the linked list are sequentially assigned to non-empty groups whose lengths form the sequence of the natural numbers (1, 2, 3, 4, ...). The length of a group is the number of nodes assigned to it. In other words,
//
//
// 	The 1st node is assigned to the first group.
// 	The 2nd and the 3rd nodes are assigned to the second group.
// 	The 4th, 5th, and 6th nodes are assigned to the third group, and so on.
//
//
// Note that the length of the last group may be less than or equal to 1 + the length of the second to last group.
//
// Reverse the nodes in each group with an even length, and return the head of the modified linked list.
//
// Example:
// Input: head = [5,2,6,3,9,1,7,3,8,4]
// Output: [5,6,2,3,9,1,4,8,3,7]
// Explanation:
// - The length of the first group is 1, which is odd, hence no reversal occurs.
// - The length of the second group is 2, which is even, hence the nodes are reversed.
// - The length of the third group is 3, which is odd, hence no reversal occurs.
// - The length of the last group is 4, which is even, hence the nodes are reversed.
//
// Constraints:
// The number of nodes in the list is in the range [1, 105].
// 	0 <= Node.val <= 105
//
// Helpful references (internal KB):
// - Linked-list implementations of collections (linked-list, ds, simulation)
//   • When to use: When you need dynamic collections that efficiently support insertions and deletions at specific points, or when memory usage needs to be precisely managed without contiguous memory allocation.
//   • Idea: This describes how fundamental data structures like stacks, queues, and bags can be implemented using linked lists, providing dynamic resizing and efficient element manipulation. Operations typically achieve O(1) time complexity for additions and removals at the ends.
//   • Invariants: The head pointer always points to the first element, or is null if the list is empty.; The tail pointer always points to the last element, or is null if the list is empty.
//   • Tips: Use a Node class to encapsulate data and a reference to the next element.; Maintain head and tail pointers for efficient O(1) operations in queues.
//   • Pitfalls: Forgetting to handle edge cases like empty lists or single-element lists.; Introducing 'loitering' by not nullifying references to removed objects, preventing garbage collection.
// - Floyd's Linked List Cycle Finding Algorithm (linked-list, two-pointers, simulation)
//   • When to use: Use this algorithm to efficiently detect if a linked list contains a cycle and, optionally, find the entry point of that cycle, using only constant extra space.
//   • Idea: This algorithm uses two pointers, one moving faster than the other, to detect if a cycle exists in a linked list. If a cycle is found, it can then determine the cycle's starting node in O(N) time complexity and O(1) space complexity.
//   • Invariants: The slow and fast pointers are always valid nodes or null.; In the detection phase, the fast pointer always covers twice the distance of the slow pointer.
//   • Tips: Initialize both slow and fast pointers at the head of the list.; Move the slow pointer by one step and the fast pointer by two steps in each iteration.
//   • Pitfalls: Forgetting to check for null on 'fast' and 'fast.next' before dereferencing them.; Incorrectly assuming the list is non-empty or has at least two nodes.
// - Josephus Problem (number, recursion, counting)
//   • When to use: Use when simulating a circular elimination process with a fixed step size, especially when seeking the survivor's position. It's particularly efficient for specific step sizes like two.
//   • Idea: The Josephus Problem determines the last remaining position in a circular arrangement after elements are eliminated at fixed intervals. The recursive solution for a step size of two has a logarithmic time complexity, O(log N), due to its divide-and-conquer nature.
//   • Invariants: The number of participants N is always positive in each recursive subproblem.; The returned position is always within the valid range [0, current N-1] (or [1, current N]).
//   • Tips: Base cases are crucial for recursive solutions, typically for N=1.; Observe patterns for specific step sizes, especially k=2, which has a simpler formula.
//   • Pitfalls: Off-by-one errors when converting between 0-indexed and 1-indexed results.; Incorrectly applying the position 'shift' after elements are eliminated in subproblems.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode reverseEvenLengthGroups(ListNode head) {
        ListNode dummy = new ListNode(0, head);
        ListNode prevGroupEnd = dummy;
        ListNode curr = head;

        int groupSize = 1;

        while (curr != null) {
            ListNode groupStart = curr;
            int count = 0;

            // Count nodes in the current group
            while (curr != null && count < groupSize) {
                curr = curr.next;
                count++;
            }

            // If the group size is even, reverse the group
            if (count % 2 == 0) {
                ListNode[] reversed = reverseGroup(groupStart, count);
                prevGroupEnd.next = reversed[0];
                prevGroupEnd = reversed[1];
            } else {
                prevGroupEnd.next = groupStart;
                prevGroupEnd = getTail(groupStart, count);
            }

            groupSize++;
        }

        return dummy.next;          
    }
}
