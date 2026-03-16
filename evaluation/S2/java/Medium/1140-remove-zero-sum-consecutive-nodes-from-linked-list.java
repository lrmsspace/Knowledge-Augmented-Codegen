// Source: https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.
//
// After doing so, return the head of the final linked list.  You may return any such answer.
//
//  
// (Note that in the examples below, all sequences are serializations of ListNode objects.)
//
// Example:
// Input: head = [1,2,-3,3,1]
// Output: [3,1]
// Note: The answer [1,2,1] would also be accepted.
//
// Constraints:
// The given linked list will contain between 1 and 1000 nodes.
// 	Each node in the linked list has -1000 <= node.val <= 1000.
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
    public ListNode removeZeroSumSublists(ListNode head) {
        ListNode dummy = new ListNode(0);
        dummy.next = head;

        Map<Integer, ListNode> prefixSumMap = new HashMap<>();
        int prefixSum = 0;
        ListNode current = dummy;

        while (current != null) {
            prefixSum += current.val;

            if (prefixSumMap.containsKey(prefixSum)) {
                ListNode prevNode = prefixSumMap.get(prefixSum);
                ListNode nodeToRemove = prevNode.next;
                int tempSum = prefixSum;

                while (nodeToRemove != current) {
                    tempSum += nodeToRemove.val;
                    prefixSumMap.remove(tempSum);
                    nodeToRemove = nodeToRemove.next;
                }

                prevNode.next = current.next;
            } else {
                prefixSumMap.put(prefixSum, current);
            }

            current = current.next;
        }

        return dummy.next;          
    }
}
