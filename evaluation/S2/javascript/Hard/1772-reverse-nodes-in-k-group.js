// Source: https://leetcode.com/problems/reverse-nodes-in-k-group/   |   Difficulty: Hard
//
// Problem Description:
// Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.
//
// k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.
//
// You may not alter the values in the list's nodes, only nodes themselves may be changed.
//
// Example:
// Input: head = [1,2,3,4,5], k = 2
// Output: [2,1,4,3,5]
//
// Constraints:
// The number of nodes in the list is n.
// 	1 <= k <= n <= 5000
// 	0 <= Node.val <= 1000
//
//
//  
// Follow-up: Can you solve the problem in O(1) extra memory space?
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
 * @param {number} k
 * @return {ListNode}
 */
var reverseKGroup = function(head, k) {
    if (!head || k <= 1) return head;

    const dummy = new ListNode(0);
    dummy.next = head;
    let groupPrev = dummy;
    
    while (true) {
        const kthNode = getKthNode(groupPrev, k);
        if (!kthNode) break;
        
        const groupNext = kthNode.next;
        let prev = groupNext;
        let curr = groupPrev.next;
        
        while (curr !== groupNext) {
            const next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }
        
        const temp = groupPrev.next;
        groupPrev.next = kthNode;
        temp.next = groupNext;
        groupPrev = temp;
    }
    
    return dummy.next;
};

function getKthNode(curr, k) {
    while (curr && k > 0) {
        curr = curr.next;
        k--;
    }
    return curr;
}