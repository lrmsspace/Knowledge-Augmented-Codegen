// Source: https://leetcode.com/problems/binary-tree-postorder-traversal/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return the postorder traversal of its nodes' values.
//
// Example:
// Input: root = [1,null,2,3]
//
// Output: [3,2,1]
//
// Explanation:
//
// Constraints:
// The number of the nodes in the tree is in the range [0, 100].
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
var postorderTraversal = function(root) {
    const result = [];
    const stack = [];
    let lastVisited = null;
    let current = root;
    while (current !== null || stack.length > 0) {
        while (current !== null) {
            stack.push(current);
            current = current.left;
        }
        const peekNode = stack[stack.length - 1];
        if (peekNode.right !== null && lastVisited !== peekNode.right) {
            current = peekNode.right;
        } else {
            result.push(peekNode.val);
            lastVisited = stack.pop();
        }
    }
    return result;
};