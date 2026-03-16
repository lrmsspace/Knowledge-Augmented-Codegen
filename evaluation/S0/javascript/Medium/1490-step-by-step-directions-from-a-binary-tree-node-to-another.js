// Source: https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree with n nodes. Each node is uniquely assigned a value from 1 to n. You are also given an integer startValue representing the value of the start node s, and a different integer destValue representing the value of the destination node t.
//
// Find the shortest path starting from node s and ending at node t. Generate step-by-step directions of such path as a string consisting of only the uppercase letters 'L', 'R', and 'U'. Each letter indicates a specific direction:
//
//
// 	'L' means to go from a node to its left child node.
// 	'R' means to go from a node to its right child node.
// 	'U' means to go from a node to its parent node.
//
//
// Return the step-by-step directions of the shortest path from node s to node t.
//
// Example:
// Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
// Output: "UURL"
// Explanation: The shortest path is: 3 → 1 → 5 → 2 → 6.
//
// Constraints:
// The number of nodes in the tree is n.
// 	2 <= n <= 105
// 	1 <= Node.val <= n
// 	All the values in the tree are unique.
// 	1 <= startValue, destValue <= n
// 	startValue != destValue
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
 * @param {number} startValue
 * @param {number} destValue
 * @return {string}
 */
var getDirections = function(root, startValue, destValue) {
    const pathToNode = (node, value, path) => {
        if (!node) return null;
        if (node.val === value) return path;
        return pathToNode(node.left, value, path + 'L') || pathToNode(node.right, value, path + 'R');
    };

    const pathToStart = pathToNode(root, startValue, '');
    const pathToDest = pathToNode(root, destValue, '');
    let i = 0;
    while (i < pathToStart.length && i < pathToDest.length && pathToStart[i] === pathToDest[i]) {
        i++;
    }
    const upMoves = 'U'.repeat(pathToStart.length - i);
    const downMoves = pathToDest.slice(i);
    return upMoves + downMoves; 
};
