// Source: https://leetcode.com/problems/rotate-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list, rotate the list to the right by k places.
//
// Example:
// Input: head = [1,2,3,4,5], k = 2
// Output: [4,5,1,2,3]
//
// Constraints:
// The number of nodes in the list is in the range [0, 500].
// 	-100 <= Node.val <= 100
// 	0 <= k <= 2 * 109
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
 * @param {number} k
 * @return {ListNode}
 */
var rotateRight = function(head, k) {
    if (!head || k === 0) return head;

    // Compute the length of the list and get the tail node
    let length = 1;
    let tail = head;
    while (tail.next) {
        tail = tail.next;
        length++;
    }
    k = k % length;
    if (k === 0) return head;

    // Find the new tail: (length - k - 1)th node
    // and the new head: (length - k)th node
    let newTail = head;
    for (let i = 0; i < length - k - 1; i++) {
        newTail = newTail.next;
    }
    let newHead = newTail.next;

    // Break the list and reattach the tail to the old head
    newTail.next = null;
    tail.next = head;

    return newHead;
};