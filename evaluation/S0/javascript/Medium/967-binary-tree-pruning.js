// Source: https://leetcode.com/problems/binary-tree-pruning/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the same tree where every subtree (of the given tree) not containing a 1 has been removed.
//
// A subtree of a node node is node plus every node that is a descendant of node.
//
// Example:
// Input: root = [1,null,0,0,1]
// Output: [1,null,0,null,1]
// Explanation: 
// Only the red nodes satisfy the property "every subtree not containing a 1".
// The diagram on the right represents the answer.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 200].
// 	Node.val is either 0 or 1.
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
var pruneTree = function(root) {
    const prune = (node) => {
        if (!node) return null;
        node.left = prune(node.left);
        node.right = prune(node.right);
        if (node.val === 0 && !node.left && !node.right) {
            return null;
        }
        return node;
    };
    return prune(root);
};