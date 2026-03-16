// Source: https://leetcode.com/problems/merge-in-between-linked-lists/   |   Difficulty: Medium
//
// Problem Description:
// You are given two linked lists: list1 and list2 of sizes n and m respectively.
//
// Remove list1's nodes from the ath node to the bth node, and put list2 in their place.
//
// The blue edges and nodes in the following figure indicate the result:
//
// Build the result list and return its head.
//
// Example:
// Input: list1 = [10,1,13,6,9,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
// Output: [10,1,13,1000000,1000001,1000002,5]
// Explanation: We remove the nodes 3 and 4 and put the entire list2 in their place. The blue edges and nodes in the above figure indicate the result.
//
// Constraints:
// 3 <= list1.length <= 104
// 	1 <= a <= b < list1.length - 1
// 	1 <= list2.length <= 104
//

/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} list1
 * @param {number} a
 * @param {number} b
 * @param {ListNode} list2
 * @return {ListNode}
 */
var mergeInBetween = function(list1, a, b, list2) {
    let dummy = new ListNode(0, list1);
    let prevA = dummy;
    for (let i = 0; i < a; i++) {
        prevA = prevA.next;
    }
    let afterB = prevA;
    for (let i = a; i <= b; i++) {
        afterB = afterB.next;
    }
    prevA.next = list2;
    let tail2 = list2;
    while (tail2.next !== null) {
        tail2 = tail2.next;
    }
    tail2.next = afterB.next;
    return dummy.next;
};