// Source: https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree and an integer distance. A pair of two different leaf nodes of a binary tree is said to be good if the length of the shortest path between them is less than or equal to distance.
//
// Return the number of good leaf node pairs in the tree.
//
// Example:
// Input: root = [1,2,3,null,4], distance = 3
// Output: 1
// Explanation: The leaf nodes of the tree are 3 and 4 and the length of the shortest path between them is 3. This is the only good pair.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 210].
// 	1 <= Node.val <= 100
// 	1 <= distance <= 10
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
 * @param {number} distance
 * @return {number}
 */
var countPairs = function(root, distance) {
    let goodPairs = 0;

    const dfs = (node) => {
        if (!node) return [];
        if (!node.left && !node.right) return [1];
        const leftDistances = dfs(node.left);
        const rightDistances = dfs(node.right);
        for (const ld of leftDistances) {
            for (const rd of rightDistances) {
                if (ld + rd <= distance) {
                    goodPairs++;
                }
            }
        }
        const currentDistances = [];
        for (const d of leftDistances) {
            if (d + 1 < distance) {
                currentDistances.push(d + 1);
            }
        }
        for (const d of rightDistances) {
            if (d + 1 < distance) {
                currentDistances.push(d + 1);
            }
        }
        return currentDistances;
    }
    dfs(root);
    return goodPairs;   
};
