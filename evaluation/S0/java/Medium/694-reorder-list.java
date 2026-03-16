// Source: https://leetcode.com/problems/reorder-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a singly linked-list. The list can be represented as:
//
//
// L0 → L1 → … → Ln - 1 → Ln
//
//
// Reorder the list to be on the following form:
//
//
// L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
//
//
// You may not modify the values in the list's nodes. Only nodes themselves may be changed.
//
// Example:
// Input: head = [1,2,3,4]
// Output: [1,4,2,3]
//
// Constraints:
// The number of nodes in the list is in the range [1, 5 * 104].
// 	1 <= Node.val <= 1000
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
    public void reorderList(ListNode head) {
        if (head == null || head.next == null) {
            return;
        }

        // Step 1: Find the middle of the linked list
        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        // Step 2: Reverse the second half of the linked list
        ListNode prev = null;
        ListNode curr = slow;
        ListNode next = null;

        while (curr != null) {
            next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        // Step 3: Merge the two halves
        ListNode first = head;
        ListNode second = prev;

        while (second.next != null) {
            ListNode temp1 = first.next;
            ListNode temp2 = second.next;

            first.next = second;
            second.next = temp1;

            first = temp1;
            second = temp2;
        }           
    }
}
