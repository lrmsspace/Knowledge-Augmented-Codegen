// Source: https://leetcode.com/problems/remove-linked-list-elements/   |   Difficulty: Easy
//
// Problem Description:
// Given the head of a linked list and an integer val, remove all the nodes of the linked list that has Node.val == val, and return the new head.
//
// Example:
// Input: head = [1,2,6,3,4,5,6], val = 6
// Output: [1,2,3,4,5]
//
// Constraints:
// The number of nodes in the list is in the range [0, 104].
// 	1 <= Node.val <= 50
// 	0 <= val <= 50
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
 * @param {number} val
 * @return {ListNode}
 */
var removeElements = function(head, val) {
    const dummy = new ListNode(0);
    dummy.next = head;
    let current = dummy;
    while (current.next !== null) {
        if (current.next.val === val) {
            current.next = current.next.next;
        } else {
            current = current.next;
        }
    }
    return dummy.next;
};