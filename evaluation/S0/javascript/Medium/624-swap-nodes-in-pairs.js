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
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @return {ListNode}
 */
var swapPairs = function(head) {
    const dummy = new ListNode(0, head);
    let current = dummy;

    while (current.next !== null && current.next.next !== null) {
        let first = current.next;
        let second = current.next.next;

        first.next = second.next;
        second.next = first;
        current.next = second;

        current = first;
    }

    return dummy.next;
};