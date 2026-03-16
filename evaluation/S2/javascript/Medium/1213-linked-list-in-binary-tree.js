// Source: https://leetcode.com/problems/linked-list-in-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary tree root and a linked list with head as the first node. 
//
// Return True if all the elements in the linked list starting from the head correspond to some downward path connected in the binary tree otherwise return False.
//
// In this context downward path means a path that starts at some node and goes downwards.
//
// Example:
// Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
// Output: true
// Explanation: Nodes in blue form a subpath in the binary Tree.
//
// Constraints:
// The number of nodes in the tree will be in the range [1, 2500].
// 	The number of nodes in the list will be in the range [1, 100].
// 	1 <= Node.val <= 100 for each node in the linked list and binary tree.
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
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {ListNode} head
 * @param {TreeNode} root
 * @return {boolean}
 */
var isSubPath = function(head, root) {
    if (!head) return true;
    if (!root) return false;
    if (root.val === head.val && dfs(head, root)) {
        return true;
    }
    return isSubPath(head, root.left) || isSubPath(head, root.right);
};
