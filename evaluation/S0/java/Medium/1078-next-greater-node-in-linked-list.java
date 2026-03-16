// Source: https://leetcode.com/problems/next-greater-node-in-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list with n nodes.
//
// For each node in the list, find the value of the next greater node. That is, for each node, find the value of the first node that is next to it and has a strictly larger value than it.
//
// Return an integer array answer where answer[i] is the value of the next greater node of the ith node (1-indexed). If the ith node does not have a next greater node, set answer[i] = 0.
//
// Example:
// Input: head = [2,1,5]
// Output: [5,5,0]
//
// Constraints:
// The number of nodes in the list is n.
// 	1 <= n <= 104
// 	1 <= Node.val <= 109
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
    public int[] nextLargerNodes(ListNode head) {
        List<Integer> values = new ArrayList<>();
        for (ListNode current = head; current != null; current = current.next) {
            values.add(current.val);
        }

        int n = values.size();
        int[] result = new int[n];
        Deque<Integer> stack = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && values.get(stack.peek()) < values.get(i)) {
                result[stack.pop()] = values.get(i);
            }
            stack.push(i);
        }

        return result;          
    }
}
