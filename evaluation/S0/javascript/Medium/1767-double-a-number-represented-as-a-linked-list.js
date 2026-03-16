// Source: https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a non-empty linked list representing a non-negative integer without leading zeroes.
//
// Return the head of the linked list after doubling it.
//
// Example:
// Input: head = [1,8,9]
// Output: [3,7,8]
// Explanation: The figure above corresponds to the given linked list which represents the number 189. Hence, the returned linked list represents the number 189 * 2 = 378.
//
// Constraints:
// The number of nodes in the list is in the range [1, 104]
// 	0 <= Node.val <= 9
// 	The input is generated such that the list represents a number that does not have leading zeros, except the number 0 itself.
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
var doubleIt = function(head) {
    let stack = [];
    let current = head;
    while (current) {
        stack.push(current.val);
        current = current.next;
    }
    let carry = 0;
    for (let i = stack.length - 1; i >= 0; i--) {
        let doubled = stack[i] * 2 + carry;
        stack[i] = doubled % 10;
        carry = Math.floor(doubled / 10);
    }
    if (carry > 0) {
        stack.unshift(carry);
    }
    let dummy = new ListNode(0);
    current = dummy;
    for (let val of stack) {
        current.next = new ListNode(val);
        current = current.next;
    }
    return dummy.next;
};