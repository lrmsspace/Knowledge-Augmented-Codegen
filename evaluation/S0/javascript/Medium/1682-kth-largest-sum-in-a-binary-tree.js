// Source: https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree and a positive integer k.
//
// The level sum in the tree is the sum of the values of the nodes that are on the same level.
//
// Return the kth largest level sum in the tree (not necessarily distinct). If there are fewer than k levels in the tree, return -1.
//
// Note that two nodes are on the same level if they have the same distance from the root.
//
// Example:
// Input: root = [5,8,9,2,1,3,7,4,6], k = 2
// Output: 13
// Explanation: The level sums are the following:
// - Level 1: 5.
// - Level 2: 8 + 9 = 17.
// - Level 3: 2 + 1 + 3 + 7 = 13.
// - Level 4: 4 + 6 = 10.
// The 2nd largest level sum is 13.
//
// Constraints:
// The number of nodes in the tree is n.
// 	2 <= n <= 105
// 	1 <= Node.val <= 106
// 	1 <= k <= n
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
 * @param {number} k
 * @return {number}
 */
var kthLargestLevelSum = function(root, k) {
    if (!root) return -1;
    const levelSums = [];
    const queue = [root];
    while (queue.length > 0) {
        const levelSize = queue.length;
        let levelSum = 0;
        for (let i = 0; i < levelSize; i++) {
            const node = queue.shift();
            levelSum += node.val;
            if (node.left) queue.push(node.left);
            if (node.right) queue.push(node.right);
        }
        levelSums.push(levelSum);
    }
    levelSums.sort((a, b) => b - a);
    return levelSums.length >= k ? levelSums[k - 1] : -1;
        
};
