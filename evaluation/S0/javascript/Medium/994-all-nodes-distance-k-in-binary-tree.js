// Source: https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.
//
// You can return the answer in any order.
//
// Example:
// Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
// Output: [7,4,1]
// Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 500].
// 	0 <= Node.val <= 500
// 	All the values Node.val are unique.
// 	target is the value of one of the nodes in the tree.
// 	0 <= k <= 1000
//

/**
 * Definition for a binary tree node.
 * function TreeNode(val) {
 *     this.val = val;
 *     this.left = this.right = null;
 * }
 */
/**
 * @param {TreeNode} root
 * @param {TreeNode} target
 * @param {number} k
 * @return {number[]}
 */
var distanceK = function(root, target, k) {
    const parentMap = new Map();

    const buildParentMap = (node, parent) => {
        if (!node) return;
        parentMap.set(node, parent);
        buildParentMap(node.left, node);
        buildParentMap(node.right, node);
    };
    buildParentMap(root, null);

    const result = [];
    const visited = new Set();
    const queue = [[target, 0]];
    visited.add(target);

    while (queue.length > 0) {
        const [node, dist] = queue.shift();
        if (dist === k) {
            result.push(node.val);
        } else if (dist < k) {
            const neighbors = [node.left, node.right, parentMap.get(node)];
            for (const neighbor of neighbors) {
                if (neighbor && !visited.has(neighbor)) {
                    visited.add(neighbor);
                    queue.push([neighbor, dist + 1]);
                }
            }
        }
    }

    return result;
};  