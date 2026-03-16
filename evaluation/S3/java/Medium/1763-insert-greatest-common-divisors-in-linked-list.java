// Source: https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list head, in which each node contains an integer value.
//
// Between every pair of adjacent nodes, insert a new node with a value equal to the greatest common divisor of them.
//
// Return the linked list after insertion.
//
// The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.
//
// Example:
// Input: head = [18,6,10,3]
// Output: [18,6,6,2,10,1,3]
// Explanation: The 1st diagram denotes the initial linked list and the 2nd diagram denotes the linked list after inserting the new nodes (nodes in blue are the inserted nodes).
// - We insert the greatest common divisor of 18 and 6 = 6 between the 1st and the 2nd nodes.
// - We insert the greatest common divisor of 6 and 10 = 2 between the 2nd and the 3rd nodes.
// - We insert the greatest common divisor of 10 and 3 = 1 between the 3rd and the 4th nodes.
// There are no more adjacent nodes, so we return the linked list.
//
// Constraints:
// The number of nodes in the list is in the range [1, 5000].
// 	1 <= Node.val <= 1000
//
// Helpful references (internal KB):
// - Extended Euclidean Algorithm (number, gcd, simulation)
//   • When to use: Use this algorithm to find integer coefficients x and y that satisfy Bézout's identity (ax + by = gcd(a,b)). It is also essential for computing modular multiplicative inverses and solving linear Diophantine equations.
//   • Idea: The Extended Euclidean Algorithm computes the greatest common divisor (GCD) of two integers 'a' and 'b', and simultaneously finds integer coefficients 'x' and 'y' such that 'ax + by = gcd(a,b)'. It operates in O(log(min(a,b))) time complexity.
//   • Invariants: x * (initial a) + y * (initial b) = current_a_value; x_1 * (initial a) + y_1 * (initial b) = current_b_value
//   • Tips: Can be implemented using either a recursive or an iterative approach.; The algorithm correctly handles negative integer inputs.
//   • Pitfalls: Incorrectly defining base cases in recursive implementations can lead to errors.; Potential for integer overflow if coefficients x or y become extremely large, though uncommon.
// - Linked-list implementations of collections (linked-list, stack, simulation)
//   • When to use: Use when a Last-In, First-Out (LIFO) data structure is required, and dynamic size with efficient O(1) push and pop operations is crucial, especially without a fixed capacity.
//   • Idea: This describes implementing a stack using a singly linked list, where elements are added and removed from the head of the list. Both push and pop operations achieve O(1) time complexity.
//   • Invariants: The 'first' pointer always points to the top element of the stack, or is null if the stack is empty.; Each node's 'next' pointer correctly links to the subsequent element in the stack, maintaining the LIFO order.
//   • Tips: Maintain a 'first' pointer to the head of the linked list, representing the stack's top.; Push operation involves creating a new node, linking it to the current 'first', then updating 'first'.
//   • Pitfalls: Forgetting to handle the empty stack case for pop, leading to `NoSuchElementException`.; Incorrectly updating the 'first' pointer during push or pop, which can break the list structure.
// - Linked-list implementations of collections (linked-list, queue, simulation)
//   • When to use: Use when frequent insertions or deletions at the beginning or end of a collection are required, or when the collection size is highly dynamic and unpredictable.
//   • Idea: Linked lists implement dynamic collections like queues and stacks by chaining nodes, each holding an item and a reference to the next node. Operations like adding or removing elements at the ends typically achieve O(1) time complexity, while random access is O(N).
//   • Invariants: The `first` pointer always references the head node, or is null if the list is empty.; The `last` pointer always references the tail node, or is null if the list is empty.
//   • Tips: Maintain separate `first` and `last` pointers for O(1) enqueue/dequeue operations.; Keep a `size` counter to provide O(1) size retrieval.
//   • Pitfalls: Forgetting to update `first` or `last` pointers correctly can lead to broken lists or memory leaks.; Null pointer exceptions are common when traversing or modifying an empty or partially traversed list.
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
    public ListNode insertGreatestCommonDivisors(ListNode head) {
        ListNode curr = head;
        while (curr != null && curr.next != null) {
            int gcd = gcd(curr.val, curr.next.val);
            ListNode newNode = new ListNode(gcd);
            newNode.next = curr.next;
            curr.next = newNode;
            curr = newNode.next;
        }
        return head;            
    }
}
