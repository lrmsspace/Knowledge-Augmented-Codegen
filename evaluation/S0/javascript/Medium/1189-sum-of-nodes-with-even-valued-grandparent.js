// Source: https://leetcode.com/problems/sum-of-nodes-with-even-valued-grandparent/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the sum of values of nodes with an even-valued grandparent. If there are no nodes with an even-valued grandparent, return 0.
//
// A grandparent of a node is the parent of its parent if it exists.
//
// Example:
// Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
// Output: 18
// Explanation: The red nodes are the nodes with even-value grandparent while the blue nodes are the even-value grandparents.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	1 <= Node.val <= 100
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
 * @return {number}
 */
var sumEvenGrandparent = function(root) {
    let sum = 0;
    const dfs = (node, parent, grandparent) => {
        if (!node) return;
        if (grandparent && grandparent.val % 2 === 0) {
            sum += node.val;
        }
        dfs(node.left, node, parent);
        dfs(node.right, node, parent);
    };
    dfs(root, null, null);
    return sum;
        
};
