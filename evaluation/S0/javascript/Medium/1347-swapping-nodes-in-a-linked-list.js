// Source: https://leetcode.com/problems/swapping-nodes-in-a-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list, and an integer k.
//
// Return the head of the linked list after swapping the values of the kth node from the beginning and the kth node from the end (the list is 1-indexed).
//
// Example:
// Input: head = [1,2,3,4,5], k = 2
// Output: [1,4,3,2,5]
//
// Constraints:
// The number of nodes in the list is n.
// 	1 <= k <= n <= 105
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
 * @param {number} k
 * @return {ListNode}
 */
var swapNodes = function(head, k) {
    let firstKNode = null;
    let secondKNode = null;
    let current = head;
    let length = 0;
    while (current) {
        length++;
        if (length === k) {
            firstKNode = current;
        }
        current = current.next;
    }
    current = head;
    for (let i = 0; i < length - k; i++) {
        current = current.next;
    }
    secondKNode = current;
    const temp = firstKNode.val;
    firstKNode.val = secondKNode.val;
    secondKNode.val = temp;
    return head;
};