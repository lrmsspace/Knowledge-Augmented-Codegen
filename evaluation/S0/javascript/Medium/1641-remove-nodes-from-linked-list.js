// Source: https://leetcode.com/problems/remove-nodes-from-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list.
//
// Remove every node which has a node with a greater value anywhere to the right side of it.
//
// Return the head of the modified linked list.
//
// Example:
// Input: head = [5,2,13,3,8]
// Output: [13,8]
// Explanation: The nodes that should be removed are 5, 2 and 3.
// - Node 13 is to the right of node 5.
// - Node 13 is to the right of node 2.
// - Node 8 is to the right of node 3.
//
// Constraints:
// The number of the nodes in the given list is in the range [1, 105].
// 	1 <= Node.val <= 105
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
var removeNodes = function(head) {
    let prev = null;
    let current = head;
    const stack = [];
    while (current) {
        while (stack.length > 0 && stack[stack.length - 1].val < current.val) {
            stack.pop();
        }
        stack.push(current);
        current = current.next;
    }
    for (let i = 0; i < stack.length; i++) {
        if (i < stack.length - 1) {
            stack[i].next = stack[i + 1];
        } else {
            stack[i].next = null;
        }
    }
    return stack[0];
};
