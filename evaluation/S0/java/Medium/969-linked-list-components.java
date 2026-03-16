// Source: https://leetcode.com/problems/linked-list-components/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list containing unique integer values and an integer array nums that is a subset of the linked list values.
//
// Return the number of connected components in nums where two values are connected if they appear consecutively in the linked list.
//
// Example:
// Input: head = [0,1,2,3], nums = [0,1,3]
// Output: 2
// Explanation: 0 and 1 are connected, so [0, 1] and [3] are the two connected components.
//
// Constraints:
// The number of nodes in the linked list is n.
// 	1 <= n <= 104
// 	0 <= Node.val < n
// 	All the values Node.val are unique.
// 	1 <= nums.length <= n
// 	0 <= nums[i] < n
// 	All the values of nums are unique.
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
    public int numComponents(ListNode head, int[] nums) {
        Set<Integer> numSet = new HashSet<>();
        for (int num : nums) {
            numSet.add(num);
        }

        int components = 0;
        boolean inComponent = false;

        ListNode current = head;
        while (current != null) {
            if (numSet.contains(current.val)) {
                if (!inComponent) {
                    components++;
                    inComponent = true;
                }
            } else {
                inComponent = false;
            }
            current = current.next;
        }

        return components;          
    }
}
