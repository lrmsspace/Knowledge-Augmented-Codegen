// Source: https://leetcode.com/problems/swap-nodes-in-pairs/   |   Difficulty: Medium
//
// Problem Description:
// Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)
//
// Example:
// Input: head = [1,2,3,4]
//
// Output: [2,1,4,3]
//
// Explanation:
//
// Constraints:
// The number of nodes in the list is in the range [0, 100].
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
    public ListNode swapPairs(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }

        ListNode newHead = head.next;
        ListNode prevTail = null;
        ListNode current = head;

        while (current != null && current.next != null) {
            ListNode firstNode = current;
            ListNode secondNode = current.next;
            ListNode nextPairHead = secondNode.next;

            // Swap the pair
            secondNode.next = firstNode;
            firstNode.next = nextPairHead;

            // Connect the previous pair's tail to the current swapped pair
            if (prevTail != null) {
                prevTail.next = secondNode;
            }

            // Update prevTail to the end of the swapped pair
            prevTail = firstNode;

            // Move to the next pair
            current = nextPairHead;
        }

        return newHead;         
    }
}
