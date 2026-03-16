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
        Map<Integer, ListNode> prefixSumMap = new HashMap<>();
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        prefixSumMap.put(0, dummy);

        int prefixSum = 0;
        for (ListNode current = dummy; current != null; current = current.next) {
            prefixSum += current.val;

            if (prefixSumMap.containsKey(prefixSum)) {
                ListNode prev = prefixSumMap.get(prefixSum);
                ListNode nodeToRemove = prev.next;
                int sumInBetween = prefixSum;

                while (nodeToRemove != current) {
                    sumInBetween += nodeToRemove.val;
                    prefixSumMap.remove(sumInBetween);
                    nodeToRemove = nodeToRemove.next;
                }

                prev.next = current.next;
            } else {
                prefixSumMap.put(prefixSum, current);
            }
        }

        return dummy.next;          
    }
}
