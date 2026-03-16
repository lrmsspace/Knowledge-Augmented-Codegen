// Source: https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/   |   Difficulty: Medium
//
// Problem Description:
// A critical point in a linked list is defined as either a local maxima or a local minima.
//
// A node is a local maxima if the current node has a value strictly greater than the previous node and the next node.
//
// A node is a local minima if the current node has a value strictly smaller than the previous node and the next node.
//
// Note that a node can only be a local maxima/minima if there exists both a previous node and a next node.
//
// Given a linked list head, return an array of length 2 containing [minDistance, maxDistance] where minDistance is the minimum distance between any two distinct critical points and maxDistance is the maximum distance between any two distinct critical points. If there are fewer than two critical points, return [-1, -1].
//
// Example:
// Input: head = [3,1]
// Output: [-1,-1]
// Explanation: There are no critical points in [3,1].
//
// Constraints:
// The number of nodes in the list is in the range [2, 105].
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
 * @return {number[]}
 */
var nodesBetweenCriticalPoints = function(head) {
    let prev = head;
    let curr = head.next;
    let index = 1;
    const criticalPoints = [];
    while (curr && curr.next) {
        if ((curr.val > prev.val && curr.val > curr.next.val) ||
            (curr.val < prev.val && curr.val < curr.next.val)) {
            criticalPoints.push(index);
        }
        prev = curr;
        curr = curr.next;
        index++;
    }
    if (criticalPoints.length < 2) {
        return [-1, -1];
    }
    let minDistance = Infinity;
    for (let i = 1; i < criticalPoints.length; i++) {
        minDistance = Math.min(minDistance, criticalPoints[i] - criticalPoints[i - 1]);
    }
    const maxDistance = criticalPoints[criticalPoints.length - 1] - criticalPoints[0];
    return [minDistance, maxDistance];  
};
