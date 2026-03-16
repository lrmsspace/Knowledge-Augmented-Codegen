// Source: https://leetcode.com/problems/reverse-linked-list/   |   Difficulty: Easy
//
// Problem Description:
// Given the head of a singly linked list, reverse the list, and return the reversed list.
//
// Example:
// Input: head = [1,2,3,4,5]
// Output: [5,4,3,2,1]
//
// Constraints:
// The number of nodes in the list is the range [0, 5000].
// 	-5000 <= Node.val <= 5000
//
//
//  
// Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?
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
    public ListNode reverseList(ListNode head) {
        ListNode prev = null;
        ListNode curr = head;

        while (curr != null) {
            ListNode nextTemp = curr.next;
            curr.next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;            
    }
}
