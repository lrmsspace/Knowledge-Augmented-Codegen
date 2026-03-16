// Source: https://leetcode.com/problems/maximum-width-of-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the maximum width of the given tree.
//
// The maximum width of a tree is the maximum width among all levels.
//
// The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.
//
// It is guaranteed that the answer will in the range of a 32-bit signed integer.
//
// Example:
// Input: root = [1,3,2,5,3,null,9]
// Output: 4
// Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).
//
// Constraints:
// The number of nodes in the tree is in the range [1, 3000].
// 	-100 <= Node.val <= 100
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
var widthOfBinaryTree = function(root) {
    if (!root) return 0;
    let maxWidth = 0;
    const queue = [[root, 0]]; // [node, index]
    while (queue.length > 0) {
        const levelLength = queue.length;
        const levelIndices = [];
        for (let i = 0; i < levelLength; i++) {
            const [node, index] = queue.shift();
            levelIndices.push(index);
            if (node.left) queue.push([node.left, 2 * index]);
            if (node.right) queue.push([node.right, 2 * index + 1]);
        }
        maxWidth = Math.max(maxWidth, levelIndices[levelIndices.length - 1] - levelIndices[0] + 1);
    }
    return maxWidth;
};