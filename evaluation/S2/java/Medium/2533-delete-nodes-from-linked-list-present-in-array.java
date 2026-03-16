// Source: https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums and the head of a linked list. Return the head of the modified linked list after removing all nodes from the linked list that have a value that exists in nums.
//
// Example:
// Input: nums = [1,2,3], head = [1,2,3,4,5]
//
// Output: [4,5]
//
// Explanation:
//
//
//
// Remove the nodes with values 1, 2, and 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	All elements in nums are unique.
// 	The number of nodes in the given list is in the range [1, 105].
// 	1 <= Node.val <= 105
// 	The input is generated such that there is at least one node in the linked list that has a value not present in nums.
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
    public ListNode modifiedList(int[] nums, ListNode head) {
        Set<Integer> numSet = new HashSet<>();
        for (int num : nums) {
            numSet.add(num);
        }

        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode current = dummy;

        while (current.next != null) {
            if (numSet.contains(current.next.val)) {
                current.next = current.next.next; // Skip the node
            } else {
                current = current.next; // Move to the next node
            }
        }

        return dummy.next; // Return the modified list head         
    }
}
