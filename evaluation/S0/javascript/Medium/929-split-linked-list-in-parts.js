// Source: https://leetcode.com/problems/split-linked-list-in-parts/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a singly linked list and an integer k, split the linked list into k consecutive linked list parts.
//
// The length of each part should be as equal as possible: no two parts should have a size differing by more than one. This may lead to some parts being null.
//
// The parts should be in the order of occurrence in the input list, and parts occurring earlier should always have a size greater than or equal to parts occurring later.
//
// Return an array of the k parts.
//
// Example:
// Input: head = [1,2,3], k = 5
// Output: [[1],[2],[3],[],[]]
// Explanation:
// The first element output[0] has output[0].val = 1, output[0].next = null.
// The last element output[4] is null, but its string representation as a ListNode is [].
//
// Constraints:
// The number of nodes in the list is in the range [0, 1000].
// 	0 <= Node.val <= 1000
// 	1 <= k <= 50
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
 * @return {ListNode[]}
 */
var splitListToParts = function(head, k) {
    let length = 0;
    let current = head;
    while (current) {
        length++;
        current = current.next;
    }

    const partLength = Math.floor(length / k);
    let remainder = length % k;
    const result = new Array(k).fill(null);
    current = head;

    for (let i = 0; i < k && current; i++) {
        result[i] = current;
        let size = partLength + (remainder > 0 ? 1 : 0);
        remainder--;

        for (let j = 1; j < size; j++) {
            current = current.next;
        }

        const next = current.next;
        current.next = null;
        current = next;
    }

    return result;
};