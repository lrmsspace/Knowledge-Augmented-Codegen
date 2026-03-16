// Source: https://leetcode.com/problems/delete-node-in-a-bst/   |   Difficulty: Medium
//
// Problem Description:
// Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.
//
// Basically, the deletion can be divided into two stages:
//
//
// 	Search for a node to remove.
// 	If the node is found, delete the node.
//
// Example:
// Input: root = [5,3,6,2,4,null,7], key = 3
// Output: [5,4,6,2,null,null,7]
// Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
// One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
// Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.
//
// Constraints:
// The number of nodes in the tree is in the range [0, 104].
// 	-105 <= Node.val <= 105
// 	Each node has a unique value.
// 	root is a valid binary search tree.
// 	-105 <= key <= 105
//
//
//  
// Follow up: Could you solve it with time complexity O(height of tree)?
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
 * @param {number} key
 * @return {TreeNode}
 */
var deleteNode = function(root, key) {
    if (!root) return null;

    if (key < root.val) {
        root.left = deleteNode(root.left, key);
    } else if (key > root.val) {
        root.right = deleteNode(root.right, key);
    } else {
        if (!root.left) {
            return root.right;
        } else if (!root.right) {
            return root.left;
        } else {
            let successor = root.right;
            while (successor.left) {
                successor = successor.left;
            }
            root.val = successor.val;
            root.right = deleteNode(root.right, successor.val);
        }
    }
    return root;
};