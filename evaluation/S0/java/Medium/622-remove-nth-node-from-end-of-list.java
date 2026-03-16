// Source: https://leetcode.com/problems/remove-nth-node-from-end-of-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list, remove the nth node from the end of the list and return its head.
//
// Example:
// Input: head = [1,2,3,4,5], n = 2
// Output: [1,2,3,5]
//
// Constraints:
// The number of nodes in the list is sz.
// 	1 <= sz <= 30
// 	0 <= Node.val <= 100
// 	1 <= n <= sz
//
//
//  
// Follow up: Could you do this in one pass?
//

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
    public ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode first = dummy;
        ListNode second = dummy;

        // Move first n+1 steps ahead
        for (int i = 0; i <= n; i++) {
            first = first.next;
        }

        // Move both pointers until first reaches the end
        while (first != null) {
            first = first.next;
            second = second.next;
        }

        // Remove the nth node from the end
        second.next = second.next.next;

        return dummy.next;          
    }
}
