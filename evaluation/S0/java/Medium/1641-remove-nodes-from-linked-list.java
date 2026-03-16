// Source: https://leetcode.com/problems/remove-nodes-from-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list.
//
// Remove every node which has a node with a greater value anywhere to the right side of it.
//
// Return the head of the modified linked list.
//
// Example:
// Input: head = [5,2,13,3,8]
// Output: [13,8]
// Explanation: The nodes that should be removed are 5, 2 and 3.
// - Node 13 is to the right of node 5.
// - Node 13 is to the right of node 2.
// - Node 8 is to the right of node 3.
//
// Constraints:
// The number of the nodes in the given list is in the range [1, 105].
// 	1 <= Node.val <= 105
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
    public ListNode removeNodes(ListNode head) {
        head = reverse(head);
        ListNode curr = head;
        int maxVal = curr.val;

        while (curr != null && curr.next != null) {
            if (curr.next.val < maxVal) {
                curr.next = curr.next.next;
            } else {
                curr = curr.next;
                maxVal = Math.max(maxVal, curr.val);
            }
        }

        return reverse(head);           
    }
}
