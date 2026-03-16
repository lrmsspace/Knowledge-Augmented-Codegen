// Source: https://leetcode.com/problems/insert-into-a-binary-search-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root node of a binary search tree (BST) and a value to insert into the tree. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.
//
// Notice that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.
//
// Example:
// Input: root = [4,2,7,1,3], val = 5
// Output: [4,2,7,1,3,5]
// Explanation: Another accepted tree is:
//
// Constraints:
// The number of nodes in the tree will be in the range [0, 104].
// 	-108 <= Node.val <= 108
// 	All the values Node.val are unique.
// 	-108 <= val <= 108
// 	It's guaranteed that val does not exist in the original BST.
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
 * @param {number} val
 * @return {TreeNode}
 */
var insertIntoBST = function(root, val) {
    if (!root) return new TreeNode(val);
    let current = root;
    while (true) {
        if (val < current.val) {
            if (!current.left) {
                current.left = new TreeNode(val);
                break;
            } else {
                current = current.left;
            }
        } else {
            if (!current.right) {
                current.right = new TreeNode(val);
                break;
            } else {
                current = current.right;
            }
        }
    }
    return root;
};