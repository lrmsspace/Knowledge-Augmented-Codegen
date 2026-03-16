// Source: https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.
//
// After doing so, return the head of the final linked list.  You may return any such answer.
//
//  
// (Note that in the examples below, all sequences are serializations of ListNode objects.)
//
// Example:
// Input: head = [1,2,-3,3,1]
// Output: [3,1]
// Note: The answer [1,2,1] would also be accepted.
//
// Constraints:
// The given linked list will contain between 1 and 1000 nodes.
// 	Each node in the linked list has -1000 <= node.val <= 1000.
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
var removeZeroSumSublists = function(head) {
    let dummy = new ListNode(0);
    dummy.next = head;
    let prefixSumMap = new Map();
    let prefixSum = 0;
    let current = dummy;
    while (current) {
        prefixSum += current.val;
        if (prefixSumMap.has(prefixSum)) {
            let prevNode = prefixSumMap.get(prefixSum);
            let nodeToRemove = prevNode.next;
            let sumInBetween = prefixSum;
            while (nodeToRemove !== current) {
                sumInBetween += nodeToRemove.val;
                prefixSumMap.delete(sumInBetween);
                nodeToRemove = nodeToRemove.next;
            }
            prevNode.next = current.next;
        } else {
            prefixSumMap.set(prefixSum, current);
        }
        current = current.next;
    }
    return dummy.next;
        
};
