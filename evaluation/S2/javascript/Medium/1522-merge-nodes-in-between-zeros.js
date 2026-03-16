// Source: https://leetcode.com/problems/merge-nodes-in-between-zeros/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list, which contains a series of integers separated by 0's. The beginning and end of the linked list will have Node.val == 0.
//
// For every two consecutive 0's, merge all the nodes lying in between them into a single node whose value is the sum of all the merged nodes. The modified list should not contain any 0's.
//
// Return the head of the modified linked list.
//
// Example:
// Input: head = [0,3,1,0,4,5,2,0]
// Output: [4,11]
// Explanation: 
// The above figure represents the given linked list. The modified list contains
// - The sum of the nodes marked in green: 3 + 1 = 4.
// - The sum of the nodes marked in red: 4 + 5 + 2 = 11.
//
// Constraints:
// The number of nodes in the list is in the range [3, 2 * 105].
// 	0 <= Node.val <= 1000
// 	There are no two consecutive nodes with Node.val == 0.
// 	The beginning and end of the linked list have Node.val == 0.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

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
var mergeNodes = function(head) {
    let current = head;
    let sum = 0;
    let newHead = null;
    let newCurrent = null;
    while (current !== null) {
        if (current.val === 0) {
            if (sum !== 0) {
                const newNode = new ListNode(sum);
                if (newHead === null) {
                    newHead = newNode;
                    newCurrent = newNode;
                } else {
                    newCurrent.next = newNode;
                    newCurrent = newNode;
                }
            }
            sum = 0;
        } else {
            sum += current.val;
        }
        current = current.next;
    }
    return newHead;
};
