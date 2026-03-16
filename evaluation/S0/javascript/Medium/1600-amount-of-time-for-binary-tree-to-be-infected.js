// Source: https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree with unique values, and an integer start. At minute 0, an infection starts from the node with value start.
//
// Each minute, a node becomes infected if:
//
//
// 	The node is currently uninfected.
// 	The node is adjacent to an infected node.
//
//
// Return the number of minutes needed for the entire tree to be infected.
//
// Example:
// Input: root = [1,5,3,null,4,10,6,9,2], start = 3
// Output: 4
// Explanation: The following nodes are infected during:
// - Minute 0: Node 3
// - Minute 1: Nodes 1, 10 and 6
// - Minute 2: Node 5
// - Minute 3: Node 4
// - Minute 4: Nodes 9 and 2
// It takes 4 minutes for the whole tree to be infected so we return 4.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 105].
// 	1 <= Node.val <= 105
// 	Each node has a unique value.
// 	A node with a value of start exists in the tree.
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
 * @param {number} start
 * @return {number}
 */
var amountOfTime = function(root, start) {
    const graph = new Map();

    const buildGraph = (node, parent) => {
        if (!node) return;
        if (!graph.has(node.val)) {
            graph.set(node.val, []);
        }
        if (parent !== null) {
            graph.get(node.val).push(parent.val);
            graph.get(parent.val).push(node.val);
        }
        buildGraph(node.left, node);
        buildGraph(node.right, node);
    };
    buildGraph(root, null);

    const queue = [];   
    const visited = new Set();
    queue.push(start);
    visited.add(start);
    let minutes = -1;

    while (queue.length > 0) {
        const size = queue.length;
        for (let i = 0; i < size; i++) {
            const current = queue.shift();
            for (const neighbor of graph.get(current)) {
                if (!visited.has(neighbor)) {
                    visited.add(neighbor);
                    queue.push(neighbor);
                }
            }
        }
        minutes++;
    }
    return minutes;
};  
