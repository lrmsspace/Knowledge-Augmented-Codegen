// Source: https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// In a linked list of size n, where n is even, the ith node (0-indexed) of the linked list is known as the twin of the (n-1-i)th node, if 0 <= i <= (n / 2) - 1.
//
//
// 	For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the twin of node 2. These are the only nodes with twins for n = 4.
//
//
// The twin sum is defined as the sum of a node and its twin.
//
// Given the head of a linked list with even length, return the maximum twin sum of the linked list.
//
// Example:
// Input: head = [5,4,2,1]
// Output: 6
// Explanation:
// Nodes 0 and 1 are the twins of nodes 3 and 2, respectively. All have twin sum = 6.
// There are no other nodes with twins in the linked list.
// Thus, the maximum twin sum of the linked list is 6.
//
// Constraints:
// The number of nodes in the list is an even integer in the range [2, 105].
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
    public int pairSum(ListNode head) {
        ListNode slow = head;
        ListNode fast = head;

        // Find the middle of the linked list using the slow and fast pointer technique
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        // Reverse the second half of the linked list
        ListNode prev = null;
        ListNode curr = slow;
        while (curr != null) {
            ListNode nextTemp = curr.next;
            curr.next = prev;
            prev = curr;
            curr = nextTemp;
        }

        // Calculate the maximum twin sum
        int maxSum = 0;
        ListNode firstHalf = head;
        ListNode secondHalf = prev; // 'prev' is now the head of the reversed second half

        while (secondHalf != null) {
            int currentSum = firstHalf.val + secondHalf.val;
            maxSum = Math.max(maxSum, currentSum);
            firstHalf = firstHalf.next;
            secondHalf = secondHalf.next;
        }

        return maxSum;          
    }
}
