// Source: https://leetcode.com/problems/n-ary-tree-postorder-traversal/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of an n-ary tree, return the postorder traversal of its nodes' values.
//
// Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)
//
// Example:
// Input: root = [1,null,3,2,4,null,5,6]
// Output: [5,6,3,2,4,1]
//
// Constraints:
// The number of nodes in the tree is in the range [0, 104].
// 	0 <= Node.val <= 104
// 	The height of the n-ary tree is less than or equal to 1000.
//
//
//  
// Follow up: Recursive solution is trivial, could you do it iteratively?
//

/**
 * // Definition for a _Node.
 * function _Node(val,children) {
 *    this.val = val;
 *    this.children = children;
 * };
 */

/**
 * @param {_Node|null} root
 * @return {number[]}
 */
var postorder = function(root) {
    const result = [];

    const traverse = (node) => {
        if (!node) return;
        for (const child of node.children) {
            traverse(child);
        }
        result.push(node.val);
    }
    traverse(root);
    return result;          
};
