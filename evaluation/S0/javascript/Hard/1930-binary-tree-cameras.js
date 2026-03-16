// Source: https://leetcode.com/problems/binary-tree-cameras/   |   Difficulty: Hard
//
// Problem Description:
// You are given the root of a binary tree. We install cameras on the tree nodes where each camera at a node can monitor its parent, itself, and its immediate children.
//
// Return the minimum number of cameras needed to monitor all nodes of the tree.
//
// Example:
// Input: root = [0,0,null,0,0]
// Output: 1
// Explanation: One camera is enough to monitor all nodes if placed as shown.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 1000].
// 	Node.val == 0
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
var minCameraCover = function(root) {
    const NOT_COVERED = 0;
    const COVERED_NO_CAMERA = 1;
    const CAMERA = 2;
    let cameras = 0;

    const dfs = (node) => {
        if (!node) {
            return COVERED_NO_CAMERA;
        }
        const leftState = dfs(node.left);
        const rightState = dfs(node.right);
        if (leftState === NOT_COVERED || rightState === NOT_COVERED) {
            cameras++;
            return CAMERA;
        }
        if (leftState === CAMERA || rightState === CAMERA) {
            return COVERED_NO_CAMERA;
        }
        return NOT_COVERED;
    };

    if (dfs(root) === NOT_COVERED) {
        cameras++;
    }
    return cameras; 
};
