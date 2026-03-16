// Source: https://leetcode.com/problems/reverse-linked-list/   |   Difficulty: Easy
//
// Problem Description:
// Given the head of a singly linked list, reverse the list, and return the reversed list.
//
// Example:
// Input: head = [1,2,3,4,5]
// Output: [5,4,3,2,1]
//
// Constraints:
// The number of nodes in the list is the range [0, 5000].
// 	-5000 <= Node.val <= 5000
//
//
//  
// Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?
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
    public ListNode reverseList(ListNode head) {
        ListNode prev = null;
        ListNode curr = head;

        while (curr != null) {
            ListNode nextTemp = curr.next; // Store the next node
            curr.next = prev;              // Reverse the current node's pointer
            prev = curr;                   // Move prev to the current node
            curr = nextTemp;               // Move to the next node
        }

        return prev; // At the end, prev will be the new head of the reversed list          
    }
}
