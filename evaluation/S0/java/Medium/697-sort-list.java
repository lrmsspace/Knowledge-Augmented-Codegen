// Source: https://leetcode.com/problems/sort-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list, return the list after sorting it in ascending order.
//
// Example:
// Input: head = [4,2,1,3]
// Output: [1,2,3,4]
//
// Constraints:
// The number of nodes in the list is in the range [0, 5 * 104].
// 	-105 <= Node.val <= 105
//
//
//  
// Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?
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
    public ListNode sortList(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }

        // Find the middle of the list
        ListNode slow = head;
        ListNode fast = head;
        ListNode prev = null;

        while (fast != null && fast.next != null) {
            prev = slow;
            slow = slow.next;
            fast = fast.next.next;
        }

        // Split the list into two halves
        prev.next = null;

        // Sort each half
        ListNode l1 = sortList(head);
        ListNode l2 = sortList(slow);

        // Merge the sorted halves
        return merge(l1, l2);           
    }
}
