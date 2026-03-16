// Source: https://leetcode.com/problems/merge-in-between-linked-lists/   |   Difficulty: Medium
//
// Problem Description:
// You are given two linked lists: list1 and list2 of sizes n and m respectively.
//
// Remove list1's nodes from the ath node to the bth node, and put list2 in their place.
//
// The blue edges and nodes in the following figure indicate the result:
//
// Build the result list and return its head.
//
// Example:
// Input: list1 = [10,1,13,6,9,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
// Output: [10,1,13,1000000,1000001,1000002,5]
// Explanation: We remove the nodes 3 and 4 and put the entire list2 in their place. The blue edges and nodes in the above figure indicate the result.
//
// Constraints:
// 3 <= list1.length <= 104
// 	1 <= a <= b < list1.length - 1
// 	1 <= list2.length <= 104
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
    public ListNode mergeInBetween(ListNode list1, int a, int b, ListNode list2) {
        ListNode curr1 = list1;
        ListNode prevA = null;
        ListNode afterB = null;

        int index = 0;
        while (curr1 != null) {
            if (index == a - 1) {
                prevA = curr1;
            }
            if (index == b + 1) {
                afterB = curr1;
                break;
            }
            curr1 = curr1.next;
            index++;
        }

        prevA.next = list2;

        ListNode curr2 = list2;
        while (curr2.next != null) {
            curr2 = curr2.next;
        }

        curr2.next = afterB;

        return list1;           
    }
}
