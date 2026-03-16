// Source: https://leetcode.com/problems/count-nodes-with-the-highest-score/   |   Difficulty: Medium
//
// Problem Description:
// There is a binary tree rooted at 0 consisting of n nodes. The nodes are labeled from 0 to n - 1. You are given a 0-indexed integer array parents representing the tree, where parents[i] is the parent of node i. Since node 0 is the root, parents[0] == -1.
//
// Each node has a score. To find the score of a node, consider if the node and the edges connected to it were removed. The tree would become one or more non-empty subtrees. The size of a subtree is the number of the nodes in it. The score of the node is the product of the sizes of all those subtrees.
//
// Return the number of nodes that have the highest score.
//
// Example:
// Input: parents = [-1,2,0,2,0]
// Output: 3
// Explanation:
// - The score of node 0 is: 3 * 1 = 3
// - The score of node 1 is: 4 = 4
// - The score of node 2 is: 1 * 1 * 2 = 2
// - The score of node 3 is: 4 = 4
// - The score of node 4 is: 4 = 4
// The highest score is 4, and three nodes (node 1, node 3, and node 4) have the highest score.
//
// Constraints:
// n == parents.length
// 	2 <= n <= 105
// 	parents[0] == -1
// 	0 <= parents[i] <= n - 1 for i != 0
// 	parents represents a valid binary tree.
//

/**
 * @param {number[]} parents
 * @return {number}
 */
var countHighestScoreNodes = function(parents) {
    const n = parents.length;
    const tree = Array.from({ length: n }, () => []);
    for (let i = 1; i < n; i++) {
        tree[parents[i]].push(i);
    }

    let maxScore = 0;
    let count = 0;

    const dfs = (node) => {
        let score = 1;
        let size = n - 1;

        for (const child of tree[node]) {
            const childSize = dfs(child);
            score *= childSize;
            size -= childSize;
        }

        if (node !== 0) {
            score *= size;
        }

        if (score > maxScore) {
            maxScore = score;
            count = 1;
        } else if (score === maxScore) {
            count++;
        }

        return n - size;
    };

    dfs(0);
    return count;
};