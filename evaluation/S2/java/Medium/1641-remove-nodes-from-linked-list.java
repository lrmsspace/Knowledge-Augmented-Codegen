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
    public ListNode removeNodes(ListNode head) {
        // We can use a stack to keep track of the nodes in the linked list.
        // We will iterate through the linked list and for each node, we will pop the nodes from the stack until we find a node with a greater value than the current node.
        // Then we will push the current node onto the stack.
        // Finally, we will construct the modified linked list from the nodes in the stack.

        Stack<ListNode> stack = new Stack<>();
        ListNode current = head;

        while (current != null) {
            while (!stack.isEmpty() && stack.peek().val < current.val) {
                stack.pop();
            }
            stack.push(current);
            current = current.next;
        }

        // Now we will construct the modified linked list from the nodes in the stack.
        ListNode newHead = null;
        ListNode newCurrent = null;

        while (!stack.isEmpty()) {
            ListNode node = stack.pop();
            if (newHead == null) {
                newHead = node;
                newCurrent = node;
            } else {
                newCurrent.next = node;
                newCurrent = newCurrent.next;
            }
        }

        if (newCurrent != null) {
            newCurrent.next = null; // Terminate the modified linked list
        }

        return newHead;         
    }
}
