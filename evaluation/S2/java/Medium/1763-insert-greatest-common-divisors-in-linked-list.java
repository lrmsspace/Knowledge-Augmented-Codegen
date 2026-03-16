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
// - N/A
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
        ListNode current = head;
        while (current != null && current.next != null) {
            int gcdValue = gcd(current.val, current.next.val);
            ListNode newNode = new ListNode(gcdValue);
            newNode.next = current.next;
            current.next = newNode;
            current = newNode.next; // Move to the next original node
        }
        return head;            
    }
}
