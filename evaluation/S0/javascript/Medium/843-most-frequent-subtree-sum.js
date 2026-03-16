// Source: https://leetcode.com/problems/most-frequent-subtree-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.
//
// The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).
//
// Example:
// Input: root = [5,2,-3]
// Output: [2,-3,4]
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
 * @return {number[]}
 */
var findFrequentTreeSum = function(root) {
    const sumCount = new Map();

    const computeSubtreeSum = (node) => {
        if (!node) return 0;
        const leftSum = computeSubtreeSum(node.left);
        const rightSum = computeSubtreeSum(node.right);
        const totalSum = node.val + leftSum + rightSum;
        sumCount.set(totalSum, (sumCount.get(totalSum) || 0) + 1);
        return totalSum;
    };
    computeSubtreeSum(root);

    let maxFrequency = 0;
    for (const freq of sumCount.values()) {
        maxFrequency = Math.max(maxFrequency, freq);
    }

    const result = [];
    for (const [sum, freq] of sumCount.entries()) {
        if (freq === maxFrequency) {
            result.push(sum);
        }
    }

    return result;
};