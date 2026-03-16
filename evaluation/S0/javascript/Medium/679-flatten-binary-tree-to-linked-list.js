// Source: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, flatten the tree into a "linked list":
//
//
// 	The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
// 	The "linked list" should be in the same order as a pre-order traversal of the binary tree.
//
// Example:
// Input: root = [1,2,5,3,4,null,6]
// Output: [1,null,2,null,3,null,4,null,5,null,6]
//
// Constraints:
// The number of nodes in the tree is in the range [0, 2000].
// 	-100 <= Node.val <= 100
//
//
//  
// Follow up: Can you flatten the tree in-place (with O(1) extra space)?
//

/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} root
 * @return {void} Do not return anything, modify root in-place instead.
 */
var flatten = function(root) {
    let current = root;
    while (current) {
        if (current.left) {
            let rightmost = current.left;
            while (rightmost.right) {
                rightmost = rightmost.right;
            }
            rightmost.right = current.right;
            current.right = current.left;
            current.left = null;
        }
        current = current.right;
    }

    return root;
};
