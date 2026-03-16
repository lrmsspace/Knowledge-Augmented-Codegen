// Source: https://leetcode.com/problems/binary-tree-preorder-traversal/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return the preorder traversal of its nodes' values.
//
// Example:
// Input: root = [1,null,2,3]
//
// Output: [1,2,3]
//
// Explanation:
//
// Constraints:
// The number of nodes in the tree is in the range [0, 100].
// 	-100 <= Node.val <= 100
//
//
//  
// Follow up: Recursive solution is trivial, could you do it iteratively?
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
 * @return {number[]}
 */
var preorderTraversal = function(root) {
    const result = [];
    const stack = [];
    if (root !== null) {
        stack.push(root);
    }

    while (stack.length > 0) {
        const node = stack.pop();
        result.push(node.val);

        if (node.right !== null) {
            stack.push(node.right);
        }
        if (node.left !== null) {
            stack.push(node.left);
        }
    }

    return result;
};