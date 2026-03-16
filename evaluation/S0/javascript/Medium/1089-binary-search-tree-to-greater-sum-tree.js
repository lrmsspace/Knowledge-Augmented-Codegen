// Source: https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
//
// As a reminder, a binary search tree is a tree that satisfies these constraints:
//
//
// 	The left subtree of a node contains only nodes with keys less than the node's key.
// 	The right subtree of a node contains only nodes with keys greater than the node's key.
// 	Both the left and right subtrees must also be binary search trees.
//
// Example:
// Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
// Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 100].
// 	0 <= Node.val <= 100
// 	All the values in the tree are unique.
//
//
//  
// Note: This question is the same as 538: https://leetcode.com/problems/convert-bst-to-greater-tree/
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
 * @return {TreeNode}
 */
var bstToGst = function(root) {
    
    let sum = 0;
    const traverse = (node) => {
        if (!node) return;
        traverse(node.right);
        sum += node.val;
        node.val = sum;
        traverse(node.left);
    };
    traverse(root);
    return root;
    
};
