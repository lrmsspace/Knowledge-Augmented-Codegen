// Source: https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.
//
// Return the smallest level x such that the sum of all the values of nodes at level x is maximal.
//
// Example:
// Input: root = [1,7,0,7,-8,null,null]
// Output: 2
// Explanation: 
// Level 1 sum = 1.
// Level 2 sum = 7 + 0 = 7.
// Level 3 sum = 7 + -8 = -1.
// So we return the level with the maximum sum which is level 2.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-105 <= Node.val <= 105
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
var maxLevelSum = function(root) {
    if (!root) return 0;
    let maxSum = -Infinity;
    let maxLevel = 1;
    let currentLevel = 1;
    const queue = [root];
    while (queue.length > 0) {
        const levelSize = queue.length;
        let currentSum = 0;
        for (let i = 0; i < levelSize; i++) {
            const node = queue.shift();
            currentSum += node.val;
            if (node.left) queue.push(node.left);
            if (node.right) queue.push(node.right);
        }
        if (currentSum > maxSum) {
            maxSum = currentSum;
            maxLevel = currentLevel;
        }
        currentLevel++;
    }
    return maxLevel;
        
};
