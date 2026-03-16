// Source: https://leetcode.com/problems/middle-of-the-linked-list/   |   Difficulty: Easy
//
// Problem Description:
// Given the head of a singly linked list, return the middle node of the linked list.
//
// If there are two middle nodes, return the second middle node.
//
// Example:
// Input: head = [1,2,3,4,5]
// Output: [3,4,5]
// Explanation: The middle node of the list is node 3.
//
// Constraints:
// The number of nodes in the list is in the range [1, 100].
// 	1 <= Node.val <= 100
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
    public ListNode middleNode(ListNode head) {
        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        return slow;            
    }
}
