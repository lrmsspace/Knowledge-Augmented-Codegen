// Source: https://leetcode.com/problems/swapping-nodes-in-a-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list, and an integer k.
//
// Return the head of the linked list after swapping the values of the kth node from the beginning and the kth node from the end (the list is 1-indexed).
//
// Example:
// Input: head = [1,2,3,4,5], k = 2
// Output: [1,4,3,2,5]
//
// Constraints:
// The number of nodes in the list is n.
// 	1 <= k <= n <= 105
// 	0 <= Node.val <= 100
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
    public ListNode swapNodes(ListNode head, int k) {
        ListNode firstK = null;
        ListNode secondK = null;
        ListNode current = head;
        int count = 1;

        while (current != null) {
            if (count == k) {
                firstK = current;
                secondK = head; // Start secondK from head when we find firstK
            } else if (firstK != null) {
                secondK = secondK.next; // Move secondK only after firstK is found
            }
            current = current.next;
            count++;
        }

        // Swap values of firstK and secondK
        if (firstK != null && secondK != null) {
            int temp = firstK.val;
            firstK.val = secondK.val;
            secondK.val = temp;
        }

        return head;            
    }
}
