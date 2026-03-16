// Source: https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a singly linked list where elements are sorted in ascending order, convert it to a height-balanced binary search tree.
//
// Example:
// Input: head = [-10,-3,0,5,9]
// Output: [0,-3,9,-10,null,5]
// Explanation: One possible answer is [0,-3,9,-10,null,5], which represents the shown height balanced BST.
//
// Constraints:
// The number of nodes in head is in the range [0, 2 * 104].
// 	-105 <= Node.val <= 105
//

/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {ListNode} head
 * @return {TreeNode}
 */
var sortedListToBST = function(head) {
    const findMiddle = (start, end) => {
        let slow = start;
        let fast = start;
        while (fast !== end && fast.next !== end) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    };
    const convertListToBST = (start, end) => {
        if (start === end) return null;
        const mid = findMiddle(start, end);
        const node = new TreeNode(mid.val);
        node.left = convertListToBST(start, mid);
        node.right = convertListToBST(mid.next, end);
        return node;
    }
    return convertListToBST(head, null);
};
