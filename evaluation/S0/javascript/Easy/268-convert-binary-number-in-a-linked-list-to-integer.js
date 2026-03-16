// Source: https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/   |   Difficulty: Easy
//
// Problem Description:
// Given head which is a reference node to a singly-linked list. The value of each node in the linked list is either 0 or 1. The linked list holds the binary representation of a number.
//
// Return the decimal value of the number in the linked list.
//
// The most significant bit is at the head of the linked list.
//
// Example:
// Input: head = [1,0,1]
// Output: 5
// Explanation: (101) in base 2 = (5) in base 10
//
// Constraints:
// The Linked List is not empty.
// 	Number of nodes will not exceed 30.
// 	Each node's value is either 0 or 1.
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
 * @return {number}
 */
var getDecimalValue = function(head) {
    let num = 0;
    let current = head;
    while (current !== null) {
        num = (num << 1) | current.val;
        current = current.next;
    }
    return num;
};
