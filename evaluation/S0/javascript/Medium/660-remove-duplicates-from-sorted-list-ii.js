// Source: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list. Return the linked list sorted as well.
//
// Example:
// Input: head = [1,2,3,3,4,4,5]
// Output: [1,2,5]
//
// Constraints:
// The number of nodes in the list is in the range [0, 300].
// 	-100 <= Node.val <= 100
// 	The list is guaranteed to be sorted in ascending order.
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
var deleteDuplicates = function(head) {
    const dummy = new ListNode(0, head);
    let prev = dummy;
    let current = head;

    while (current) {
        // Check if current node has duplicates
        if (current.next && current.val === current.next.val) {
            // Skip all nodes with the same value
            while (current.next && current.val === current.next.val) {
                current = current.next;
            }
            // Remove the last duplicate node
            prev.next = current.next;
        } else {
            // No duplicates, move prev pointer
            prev = current;
        }
        current = current.next;
    }

    return dummy.next;
};  