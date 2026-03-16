// Source: https://leetcode.com/problems/deepest-leaves-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the sum of values of its deepest leaves.
//
// Example:
// Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
// Output: 15
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
var deepestLeavesSum = function(root) {
    if (!root) return 0;
    let queue = [root];
    let sum = 0;
    while (queue.length) {
        let levelSize = queue.length;
        sum = 0;
        for (let i = 0; i < levelSize; i++) {
            let node = queue.shift();
            sum += node.val;
            if (node.left) queue.push(node.left);
            if (node.right) queue.push(node.right);
        }
    }
    return sum;
        
};
